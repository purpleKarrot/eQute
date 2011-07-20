/* Copyright (c) 2009, Marc Treib <treib@in.tum.de> 
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 2.1 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include "qtGLWidget.h"

#include <QtCore/QCoreApplication>
#include <QtCore/QMutexLocker>
#include <QtCore/QPoint>
#include <QtCore/QSize>
#include <QtGui/QMouseEvent>
#include <QtGui/QKeyEvent>
#include <QtGui/QMoveEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QShowEvent>
#include <QtGui/QHideEvent>
#include <QtGui/QCloseEvent>

#include "eqShutdownEvent.h"
#include "qtWindow.h"

namespace eqQt
{

QtGLWidget::QtGLWidget(QtWindow* window, QWidget* pParent) :
		QGLWidget(window->getQGLContext(), pParent, window->getShareQtGLWidget()), m_pQtWindow(window), m_qtEventHandler(window)
{
	setAutoBufferSwap(false);

	QMutexLocker locker(&m_mutex);

	m_pQtWindow->setQtGLWidget(this);
	EQCHECK( m_pQtWindow->registerListener( this ));
}

QtGLWidget::~QtGLWidget()
{
	QMutexLocker locker(&m_mutex);

	if (m_pQtWindow)
	{
		EQCHECK( m_pQtWindow->unregisterListener( this ));
	}
}

eqQt::QtWindow* QtGLWidget::lockQtWindow()
{
	m_mutex.lock();
	return m_pQtWindow;
}

void QtGLWidget::unlockQtWindow()
{
	m_mutex.unlock();
}

bool QtGLWidget::event(QEvent* pEvent)
{
	switch (pEvent->type())
	{
	case EqShutdownEvent::EqShutdown:
		eqShutdownEvent((EqShutdownEvent*) pEvent);
		return true;

	default:
		return QGLWidget::event(pEvent);
	}
}

void QtGLWidget::mousePressEvent(QMouseEvent* pEvent)
{
	QMutexLocker locker(&m_mutex);

	m_qtEventHandler.mousePressEvent(this, pEvent);
}

void QtGLWidget::mouseReleaseEvent(QMouseEvent* pEvent)
{
	QMutexLocker locker(&m_mutex);

	m_qtEventHandler.mouseReleaseEvent(this, pEvent);
}

void QtGLWidget::mouseMoveEvent(QMouseEvent* pEvent)
{
	QMutexLocker locker(&m_mutex);

	m_qtEventHandler.mouseMoveEvent(this, pEvent);
}

void QtGLWidget::keyPressEvent(QKeyEvent* pEvent)
{
	QMutexLocker locker(&m_mutex);

	m_qtEventHandler.keyPressEvent(this, pEvent);
}

void QtGLWidget::keyReleaseEvent(QKeyEvent* pEvent)
{
	QMutexLocker locker(&m_mutex);

	m_qtEventHandler.keyReleaseEvent(this, pEvent);
}

void QtGLWidget::paintEvent(QPaintEvent* pEvent)
{
	QMutexLocker locker(&m_mutex);

	m_qtEventHandler.paintEvent(this, pEvent);
}

void QtGLWidget::moveEvent(QMoveEvent* pEvent)
{
	QMutexLocker locker(&m_mutex);

	m_qtEventHandler.moveEvent(this, pEvent);
}

void QtGLWidget::resizeEvent(QResizeEvent* pEvent)
{
	QMutexLocker locker(&m_mutex);

	m_qtEventHandler.resizeEvent(this, pEvent);
}

void QtGLWidget::showEvent(QShowEvent* pEvent)
{
	QMutexLocker locker(&m_mutex);

	m_qtEventHandler.showEvent(this, pEvent);
}

void QtGLWidget::hideEvent(QHideEvent* pEvent)
{
	QMutexLocker locker(&m_mutex);

	m_qtEventHandler.hideEvent(this, pEvent);
}

void QtGLWidget::closeEvent(QCloseEvent* pEvent)
{
	QMutexLocker locker(&m_mutex);

	// this is only received by top-level windows,
	// so we'll probably never get here
	m_qtEventHandler.closeEvent(this, pEvent);
}

void QtGLWidget::eqShutdownEvent(EqShutdownEvent* pEvent)
{
	// default implementation does nothing
}

void QtGLWidget::beforeConfigExit()
{
	QMutexLocker locker(&m_mutex);

	m_pQtWindow = 0;
	m_qtEventHandler.setQtWindow(0);
}

void QtGLWidget::afterConfigExit()
{
	// send an EqShutdownEvent to ourselves, to be handled in the main thread
	EqShutdownEvent* pEvent = new EqShutdownEvent();
	qApp->postEvent(this, pEvent);
}

} // namespace eqQt
