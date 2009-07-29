
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

#ifndef EQQT_QTMAINWINDOW_H
#define EQQT_QTMAINWINDOW_H


#include <eq/client/event.h>

#include <QtGui/QMainWindow>


class QKeyEvent;
class QCloseEvent;


namespace eqQt
{
	class QtEventHandler;
	class QtWindowIF;

	// Implementation of a QMainWindow that forwards events it receives
	// to a QtEventHandler (if one is set)
	// Meant to be subclassed by an application-specific MainWindow
	class QtMainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		QtMainWindow( QWidget* pParent = 0 );
		virtual ~QtMainWindow();

	protected:
		QtEventHandler*	getQtEventHandler()									 { return m_pQtEventHandler; }
		void			setQtEventHandler( QtEventHandler* pQtEventHandler ) { m_pQtEventHandler = pQtEventHandler; }

		virtual void keyPressEvent(   QKeyEvent* pEvent );
		virtual void keyReleaseEvent( QKeyEvent* pEvent );

		virtual void closeEvent( QCloseEvent* pEvent );

	private:
		QtEventHandler*		m_pQtEventHandler;
	};
}


#endif // EQQT_QTMAINWINDOW_H
