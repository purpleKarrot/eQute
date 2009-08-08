
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

#include <QtCore/QCoreApplication>
#include <QtCore/QMutexLocker>
#include <QtGui/QKeyEvent>
#include <QtGui/QCloseEvent>

#include "eqShutdownEvent.h"
#include "qtWindow.h"


namespace eqQt
{
	QtMainWindow::QtMainWindow( QtWindowIF* pQtWindow, QWidget* pParent )
		: QMainWindow( pParent ), m_pQtWindow( pQtWindow ), m_qtEventHandler( pQtWindow )
	{
		QMutexLocker locker( &m_mutex );

		EQCHECK( m_pQtWindow->registerListener( this ) );
	}

	QtMainWindow::~QtMainWindow()
	{
		QMutexLocker locker( &m_mutex );

		if( m_pQtWindow ) {
			EQCHECK( m_pQtWindow->unregisterListener( this ) );
		}
	}

	eqQt::QtWindowIF* QtMainWindow::lockQtWindow()
	{
		m_mutex.lock();
		return m_pQtWindow;
	}

	void QtMainWindow::unlockQtWindow()
	{
		m_mutex.unlock();
	}

	bool QtMainWindow::event( QEvent* pEvent )
	{
		switch( pEvent->type() ) {
			case EqShutdownEvent::EqShutdown:
				eqShutdownEvent( ( EqShutdownEvent* )pEvent );
				return true;

			default:
				return QMainWindow::event( pEvent );
		}
	}

	void QtMainWindow::keyPressEvent( QKeyEvent* pEvent )
	{
		QMutexLocker locker( &m_mutex );

		m_qtEventHandler.keyPressEvent( this, pEvent );
	}

	void QtMainWindow::keyReleaseEvent( QKeyEvent* pEvent )
	{
		QMutexLocker locker( &m_mutex );

		m_qtEventHandler.keyReleaseEvent( this, pEvent );
	}

	void QtMainWindow::closeEvent( QCloseEvent* pEvent )
	{
		QMutexLocker locker( &m_mutex );

		m_qtEventHandler.closeEvent( this, pEvent );
	}

	void QtMainWindow::eqShutdownEvent( EqShutdownEvent* pEvent )
	{
		close();
	}

	void QtMainWindow::beforeConfigExit()
	{
		QMutexLocker locker( &m_mutex );

		// unregister the qtwindow, so no more events will be sent there
		m_pQtWindow = 0;
		m_qtEventHandler.setQtWindow( 0 );
	}

	void QtMainWindow::afterConfigExit()
	{
		// send an EqShutdownEvent to ourselves, to be handled in the main thread
		EqShutdownEvent* pEvent = new EqShutdownEvent();
		qApp->postEvent( this, pEvent );
	}
}
