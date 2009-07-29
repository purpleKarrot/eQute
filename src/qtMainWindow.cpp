
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

#include "qtMainWindow.h"

#include <QtGui/QKeyEvent>
#include <QtGui/QCloseEvent>

#include "qtEventHandler.h"


namespace eqQt
{
	QtMainWindow::QtMainWindow( QWidget* pParent )
		: QMainWindow( pParent ), m_pQtEventHandler( 0 )
	{
	}

	QtMainWindow::~QtMainWindow()
	{
	}

	void QtMainWindow::keyPressEvent( QKeyEvent* pEvent )
	{
		if( m_pQtEventHandler ) {
			m_pQtEventHandler->keyPressEvent( this, pEvent );
		}
	}

	void QtMainWindow::keyReleaseEvent( QKeyEvent* pEvent )
	{
		if( m_pQtEventHandler ) {
			m_pQtEventHandler->keyReleaseEvent( this, pEvent );
		}
	}

	void QtMainWindow::closeEvent( QCloseEvent* pEvent )
	{
		if( m_pQtEventHandler ) {
			m_pQtEventHandler->closeEvent( this, pEvent );
		}
	}
}
