
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


#include <eq/eq.h>
#include <eq/client/event.h>

#include <QtGui/QMouseEvent>
#include <QtOpenGL/QGLWidget>

#include "qtEventHandler.h"

class QPaintEvent;
class QMoveEvent;
class QResizeEvent;
class QShowEvent;
class QHideEvent;
class QCloseEvent;


namespace eqQt
{
	class QtEventHandler;

	// Implementation of a QGLWidget (basically a drawable) that forwards
	// events it receives to its QtEventHandler
	class QtGLWidget : public QGLWidget
	{
		Q_OBJECT

	public:
		QtGLWidget( QtWindowIF* pQtWindow, QGLContext* pGLContext, QWidget* pParent );
		~QtGLWidget();

		QGLContext* getQGLContext() { return m_pGLContext; }

		QtEventHandler* getQtEventHandler() { return &m_qtEventHandler; }

	protected:
		virtual void mousePressEvent(   QMouseEvent* pEvent );
		virtual void mouseReleaseEvent( QMouseEvent* pEvent );
		virtual void mouseMoveEvent(    QMouseEvent* pEvent );

		virtual void keyPressEvent(   QKeyEvent* pEvent );
		virtual void keyReleaseEvent( QKeyEvent* pEvent );

		virtual void paintEvent(  QPaintEvent*  pEvent );
		virtual void moveEvent(   QMoveEvent*   pEvent );
		virtual void resizeEvent( QResizeEvent* pEvent );
		virtual void showEvent(   QShowEvent*   pEvent );
		virtual void hideEvent(   QHideEvent*   pEvent );
		virtual void closeEvent(  QCloseEvent*  pEvent );

	private:
		QGLContext*		m_pGLContext;

		QtEventHandler	m_qtEventHandler;
	};
}


#endif // EQQT_QTGLWIDGET_H
