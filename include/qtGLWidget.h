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

#ifndef EQQT_QTGLWIDGET_H
#define EQQT_QTGLWIDGET_H

#include <eq/client/event.h>
#include <GL/glew.h>

#include <QtCore/QMutex>
#include <QtOpenGL/QGLWidget>

#include "qtEventHandler.h"
#include "qtWindowListener.h"

class QMouseEvent;
class QKeyEvent;
class QPaintEvent;
class QMoveEvent;
class QResizeEvent;
class QShowEvent;
class QHideEvent;
class QCloseEvent;

namespace eqQt
{

class EqShutdownEvent;
class QtWindowIF;

// Implementation of a QGLWidget (basically a drawable) that forwards
// events it receives to its QtEventHandler.
class QtGLWidget: public QGLWidget, protected QtWindowListener
{
public:
	QtGLWidget(QtWindowIF* pQtWindow, QWidget* pParent);
	virtual ~QtGLWidget();

protected:
	eqQt::QtWindowIF* lockQtWindow();
	void unlockQtWindow();

	virtual bool event(QEvent* pEvent);

	virtual void mousePressEvent(QMouseEvent* pEvent);
	virtual void mouseReleaseEvent(QMouseEvent* pEvent);
	virtual void mouseMoveEvent(QMouseEvent* pEvent);

	virtual void keyPressEvent(QKeyEvent* pEvent);
	virtual void keyReleaseEvent(QKeyEvent* pEvent);

	virtual void paintEvent(QPaintEvent* pEvent);
	virtual void moveEvent(QMoveEvent* pEvent);
	virtual void resizeEvent(QResizeEvent* pEvent);
	virtual void showEvent(QShowEvent* pEvent);
	virtual void hideEvent(QHideEvent* pEvent);
	virtual void closeEvent(QCloseEvent* pEvent);

	virtual void eqShutdownEvent(EqShutdownEvent* pEvent);

	virtual void beforeConfigExit();
	virtual void afterConfigExit();

private:
	QtWindowIF* m_pQtWindow;
	QMutex m_mutex;

	QtEventHandler m_qtEventHandler;
};

} // namespace eqQt

#endif // EQQT_QTGLWIDGET_H
