
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

#include <QtCore/QPoint>
#include <QtCore/QSize>
#include <QtGui/QMoveEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QShowEvent>
#include <QtGui/QHideEvent>
#include <QtGui/QCloseEvent>

#include "qtWindow.h"


namespace eqQt
{
	QtGLWidget::QtGLWidget( QtWindowIF* pQtWindow, QGLContext* pGLContext, QWidget* pParent )
		: QGLWidget( pGLContext, pParent ), m_pGLContext( pGLContext ), m_qtEventHandler( pQtWindow )
	{
		setAutoBufferSwap( false );
	}

	QtGLWidget::~QtGLWidget()
	{
	}

	void QtGLWidget::mousePressEvent( QMouseEvent* pEvent )
	{
		m_qtEventHandler.mousePressEvent( this, pEvent );
	}

	void QtGLWidget::mouseReleaseEvent( QMouseEvent* pEvent )
	{
		m_qtEventHandler.mouseReleaseEvent( this, pEvent );
	}

	void QtGLWidget::mouseMoveEvent( QMouseEvent* pEvent )
	{
		m_qtEventHandler.mouseMoveEvent( this, pEvent );
	}

	void QtGLWidget::keyPressEvent( QKeyEvent* pEvent )
	{
		m_qtEventHandler.keyPressEvent( this, pEvent );
	}

	void QtGLWidget::keyReleaseEvent( QKeyEvent* pEvent )
	{
		m_qtEventHandler.keyReleaseEvent( this, pEvent );
	}

	void QtGLWidget::paintEvent( QPaintEvent* pEvent )
	{
		// do nothing, the equalizer thread handles this
		//TODO maybe create an EXPOSE event?
	}

	void QtGLWidget::moveEvent( QMoveEvent* pEvent )
	{
		m_qtEventHandler.moveEvent( this, pEvent );
	}

	void QtGLWidget::resizeEvent( QResizeEvent* pEvent )
	{
		m_qtEventHandler.resizeEvent( this, pEvent );
	}

	void QtGLWidget::showEvent( QShowEvent* pEvent )
	{
		m_qtEventHandler.showEvent( this, pEvent );
	}

	void QtGLWidget::hideEvent( QHideEvent* pEvent )
	{
		m_qtEventHandler.hideEvent( this, pEvent );
	}

	void QtGLWidget::closeEvent( QCloseEvent* pEvent )
	{
		// this is only received by top-level windows,
		// so we'll probably never get here
		m_qtEventHandler.closeEvent( this, pEvent );
	}
}
