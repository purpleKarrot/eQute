
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

#include <QMetaType>
#include <QDataStream>
#include <QTextStream>
#include <QtCore/QVariant>
#include <QtCore/QDir>
#include <QtGui/QCursor>
#include <QtGui/QPrinter>

#include "qtWindow.h"

#include <eq/client/global.h>

#undef None
#undef KeyPress
#undef KeyRelease
#undef FocusIn
#undef FocusOut
#undef FontChange

#include <QtCore/QCoreApplication>
#include <QtCore/QWaitCondition>
#include <QtOpenGL/QtOpenGL>

#include "qtGLContextCreator.h"
#include "qtGLContextRequestEvent.h"
#include "qtGLWidget.h"


namespace eqQt
{
	bool QtWindowIF::configInit()
	{
		notifyListenersBeforeConfigInit();

		bool result = configInitImpl();

		notifyListenersAfterConfigInit( result );

		return result;
	}

	void QtWindowIF::configExit()
	{
		notifyListenersBeforeConfigExit();

		configExitImpl();

		notifyListenersAfterConfigExit();
	}

	void QtWindowIF::makeCurrent() const
	{
		notifyListenersBeforeMakeCurrent();

		makeCurrentImpl();

		notifyListenersAfterMakeCurrent();
	}

	void QtWindowIF::swapBuffers()
	{
		notifyListenersBeforeSwapBuffers();

		swapBuffersImpl();

		notifyListenersAfterSwapBuffers();
	}

	bool QtWindowIF::registerListener( QtWindowListener* pListener )
	{
		m_listenersMutex.lock();

		std::pair< ListenerSet::iterator, bool > inserted = m_listeners.insert( pListener );

		m_listenersMutex.unlock();

		return inserted.second;
	}

	bool QtWindowIF::unregisterListener( QtWindowListener* pListener )
	{
		m_listenersMutex.lock();

		ListenerSet::size_type erased = m_listeners.erase( pListener );

		m_listenersMutex.unlock();

		return erased > 0;
	}

	void QtWindowIF::unregisterAllListeners()
	{
		m_listenersMutex.lock();

		m_listeners.clear();

		m_listenersMutex.unlock();
	}

	void QtWindowIF::makeCurrentImpl() const
	{
		GLWindow::makeCurrent();
	}

	void QtWindowIF::notifyListenersBeforeConfigInit()
	{
		m_listenersMutex.lock();
		ListenerSet::iterator it    = m_listeners.begin(),
							  itEnd = m_listeners.end();
		m_listenersMutex.unlock();

		while( it != itEnd ) {
			QtWindowListener* pListener = *it;

			// increment iterator before notifying listener,
			// so this won't break if the listener unregisters itself
			m_listenersMutex.lock();
			it++;
			m_listenersMutex.unlock();

			pListener->beforeConfigInit();
		}
	}

	void QtWindowIF::notifyListenersAfterConfigInit( bool success )
	{
		m_listenersMutex.lock();
		ListenerSet::iterator it    = m_listeners.begin(),
							  itEnd = m_listeners.end();
		m_listenersMutex.unlock();

		while( it != itEnd ) {
			QtWindowListener* pListener = *it;

			// increment iterator before notifying listener,
			// so this won't break if the listener unregisters itself
			m_listenersMutex.lock();
			it++;
			m_listenersMutex.unlock();

			pListener->afterConfigInit( success );
		}
	}

	void QtWindowIF::notifyListenersBeforeConfigExit()
	{
		m_listenersMutex.lock();
		ListenerSet::iterator it    = m_listeners.begin(),
							  itEnd = m_listeners.end();
		m_listenersMutex.unlock();

		while( it != itEnd ) {
			QtWindowListener* pListener = *it;

			// increment iterator before notifying listener,
			// so this won't break if the listener unregisters itself
			m_listenersMutex.lock();
			it++;
			m_listenersMutex.unlock();

			pListener->beforeConfigExit();
		}
	}

	void QtWindowIF::notifyListenersAfterConfigExit()
	{
		m_listenersMutex.lock();
		ListenerSet::iterator it    = m_listeners.begin(),
							  itEnd = m_listeners.end();
		m_listenersMutex.unlock();

		while( it != itEnd ) {
			QtWindowListener* pListener = *it;

			// increment iterator before notifying listener,
			// so this won't break if the listener unregisters itself
			m_listenersMutex.lock();
			it++;
			m_listenersMutex.unlock();

			pListener->afterConfigExit();
		}
	}

    void QtWindowIF::notifyListenersBeforeMakeCurrent() const
	{
		m_listenersMutex.lock();
		ListenerSet::const_iterator	it    = m_listeners.begin(),
									itEnd = m_listeners.end();
		m_listenersMutex.unlock();

		while( it != itEnd ) {
			QtWindowListener* pListener = *it;

			// increment iterator before notifying listener,
			// so this won't break if the listener unregisters itself
			m_listenersMutex.lock();
			it++;
			m_listenersMutex.unlock();

			pListener->beforeMakeCurrent();
		}
	}

    void QtWindowIF::notifyListenersAfterMakeCurrent() const
	{
		m_listenersMutex.lock();
		ListenerSet::const_iterator	it    = m_listeners.begin(),
									itEnd = m_listeners.end();
		m_listenersMutex.unlock();

		while( it != itEnd ) {
			QtWindowListener* pListener = *it;

			// increment iterator before notifying listener,
			// so this won't break if the listener unregisters itself
			m_listenersMutex.lock();
			it++;
			m_listenersMutex.unlock();

			pListener->afterMakeCurrent();
		}
	}

    void QtWindowIF::notifyListenersBeforeSwapBuffers()
	{
		m_listenersMutex.lock();
		ListenerSet::iterator it    = m_listeners.begin(),
							  itEnd = m_listeners.end();
		m_listenersMutex.unlock();

		while( it != itEnd ) {
			QtWindowListener* pListener = *it;

			// increment iterator before notifying listener,
			// so this won't break if the listener unregisters itself
			m_listenersMutex.lock();
			it++;
			m_listenersMutex.unlock();

			pListener->beforeSwapBuffers();
		}
	}

    void QtWindowIF::notifyListenersAfterSwapBuffers()
	{
		m_listenersMutex.lock();
		ListenerSet::iterator it    = m_listeners.begin(),
							  itEnd = m_listeners.end();
		m_listenersMutex.unlock();

		while( it != itEnd ) {
			QtWindowListener* pListener = *it;

			// increment iterator before notifying listener,
			// so this won't break if the listener unregisters itself
			m_listenersMutex.lock();
			it++;
			m_listenersMutex.unlock();

			pListener->afterSwapBuffers();
		}
	}


	QtWindow::QtWindow( eq::Window* pParent )
		: QtWindowIF( pParent ), m_pContext( 0 ), m_pWidget( 0 )
	{
	}

	QtWindow::~QtWindow()
	{
	}

	QtGLWidget* QtWindow::getShareQtGLWidget()
	{
		eq::Window* pShareWindow = getWindow()->getSharedContextWindow();
		if( pShareWindow ) {
			eq::SystemWindow* pShareOSWindow = pShareWindow->getSystemWindow();
			QtWindow* pShareQtWindow = dynamic_cast< QtWindow* >( pShareOSWindow );

			if( pShareQtWindow ) {
				return pShareQtWindow->getQtGLWidget();
			}
		}

		return 0;
	}

	const QtGLWidget* QtWindow::getShareQtGLWidget() const
	{
		const eq::Window* pShareWindow = getWindow()->getSharedContextWindow();
		if( pShareWindow ) {
			const eq::SystemWindow* pShareOSWindow = pShareWindow->getSystemWindow();
			const QtWindow* pShareQtWindow = dynamic_cast< const QtWindow* >( pShareOSWindow );

			if( pShareQtWindow ) {
				return pShareQtWindow->getQtGLWidget();
			}
		}

		return 0;
	}

	bool QtWindow::configInitImpl()
	{
		QGL::FormatOptions options = 0;
		options |= QGL::Rgba;
		options |= QGL::DirectRendering;

		QGLFormat format( options );

		const int colorSize = getIAttribute( eq::Window::IATTR_PLANES_COLOR );
		if( colorSize > 0 || colorSize == eq::AUTO )
		{
			const int colorBits = ( colorSize > 0 ? colorSize : 8 );
			format.setRedBufferSize( colorBits );
			format.setGreenBufferSize( colorBits );
			format.setBlueBufferSize( colorBits );
		}

		const int alphaSize = getIAttribute( eq::Window::IATTR_PLANES_ALPHA );
		if( alphaSize > 0 || alphaSize == eq::AUTO )
		{
			format.setAlpha( true );
			const int alphaBits = ( alphaSize > 0 ? alphaSize : 8 );
			format.setAlphaBufferSize( alphaBits );
		}
		else
		{
			format.setAlpha( false );
		}

		const int depthSize = getIAttribute( eq::Window::IATTR_PLANES_DEPTH );
		if( depthSize > 0  || depthSize == eq::AUTO )
		{
			format.setDepth( true );
			const int depthBits = ( depthSize > 0 ? depthSize : 8 );
			format.setDepthBufferSize( depthBits );
		}
		else
		{
			format.setDepth( false );
		}

		const int stencilSize = getIAttribute( eq::Window::IATTR_PLANES_STENCIL );
		if( stencilSize > 0 || stencilSize == eq::AUTO )
		{
			format.setStencil( true );
			const int stencilBits = ( stencilSize > 0 ? stencilSize : 1 );
			format.setStencilBufferSize( stencilBits );
		}
		else
		{
			format.setStencil( false );
		}

		const int accumSize  = getIAttribute( eq::Window::IATTR_PLANES_ACCUM );
		const int accumAlpha = getIAttribute( eq::Window::IATTR_PLANES_ACCUM_ALPHA );
		if( accumSize >= 0 )
		{
			format.setAccum( true );
			//TODO does this work as intended? (-> separate r,g,b channels?!)
			const int accumAlphaBits = ( accumAlpha >= 0 ? accumAlpha : accumSize );
			const int accumBits = accumAlphaBits + 3 * accumSize;
			format.setAccumBufferSize( accumBits );
		}
		else if( accumAlpha >= 0 )
		{
			format.setAccum( true );
			format.setAccumBufferSize( accumAlpha );
		}
		else
		{
			format.setAccum( false );
		}

		const int samplesSize  = getIAttribute( eq::Window::IATTR_PLANES_SAMPLES );
		if( samplesSize >= 0 )
		{
			format.setSampleBuffers( true );
			format.setSamples( samplesSize );
			//TODO is there a way to check if multisampling is actually available?
		}
		else
		{
			format.setSampleBuffers( false );
		}

		if( getIAttribute( eq::Window::IATTR_HINT_STEREO ) == eq::ON ||
			( getIAttribute( eq::Window::IATTR_HINT_STEREO )   == eq::AUTO && 
			  getIAttribute( eq::Window::IATTR_HINT_DRAWABLE ) == eq::WINDOW ) )
		{
			format.setStereo( true );
		}
		else
		{
			format.setStereo( false );
		}

		if( getIAttribute( eq::Window::IATTR_HINT_DOUBLEBUFFER ) == eq::ON ||
			( getIAttribute( eq::Window::IATTR_HINT_DOUBLEBUFFER ) == eq::AUTO && 
			  getIAttribute( eq::Window::IATTR_HINT_DRAWABLE )     == eq::WINDOW ) )
		{
			format.setDoubleBuffer( true );
		}
		else
		{
			format.setDoubleBuffer( false );
		}

		// HACK: require GL 3.1
		//       if we don't do this, Qt 4.7.2 creates a 2.1 context (?!)
		format.setVersion( 3, 1 );

		if( getIAttribute( eq::Window::IATTR_HINT_DRAWABLE ) != eq::WINDOW ) {
			EQWARN << "Unsupported drawable type " << getIAttribute( eq::Window::IATTR_HINT_DRAWABLE )
				   << "for QtWindow, creating a window" << std::endl;
		}

		if( !createContext( format ) )
			return false;

		makeCurrent();
		initGLEW();

		return true;
	}

	void QtWindow::configExitImpl()
	{
	}

	void QtWindow::makeCurrentImpl() const
	{
		EQASSERT( m_pContext && m_pContext->isValid() );

		m_pContext->makeCurrent();
	}

	void QtWindow::swapBuffersImpl()
	{
		EQASSERT( m_pContext && m_pContext->isValid() );

		m_pContext->swapBuffers();
	}

	void QtWindow::joinNVSwapBarrier( const uint32_t group, const uint32_t barrier )
	{
		if( group == 0 && barrier == 0 )
			return;

		//TODO implement this?
		EQWARN << "QtWindow::joinNVSwapBarrier: NV Swap group extension not supported for Qt windows" << endl;
	}

	bool QtWindow::createContext( const QGLFormat& format )
	{
		EQASSERT( !m_pContext );

		m_pContext = new QGLContext( format );

		QtGLWidget* pShareWidget = getShareQtGLWidget();
		if( pShareWidget ) {
			// make share context un-current, otherwise sharing fails
			pShareWidget->doneCurrent();
		}

		QWaitCondition* pWaitCondition = new QWaitCondition();
		QtGLContextRequestEvent* pEvent = new QtGLContextRequestEvent( this, pWaitCondition );

		QMutex mutex;
		mutex.lock();
		qApp->postEvent( QtGLContextCreator::getInstance(), pEvent );
		pWaitCondition->wait( &mutex );
		mutex.unlock();

		delete pWaitCondition;

		bool sharing = m_pContext->isSharing();
		if( pShareWidget && !m_pContext->isSharing() ) {
			EQWARN << "QtWindow::createContext: context sharing failed!" << std::endl;
		}

		return m_pContext->isValid();
	}
}
