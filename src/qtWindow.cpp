
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

#include "qtWindow.h"

#include <eq/eq.h>

#include <QtCore/QCoreApplication>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>
#include <QtOpenGL/QtOpenGL>

#include "qtGLContextCreator.h"
#include "qtGLContextRequestEvent.h"


namespace eqQt
{
	QtWindow::QtWindow( eq::Window* pParent )
		: QtWindowIF( pParent ), m_pContext( 0 )
	{
	}

	QtWindow::~QtWindow()
	{
	}

	bool QtWindow::configInit()
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

		const int depthSize = getIAttribute( eq::Window::IATTR_PLANES_DEPTH );
		if( depthSize > 0  || depthSize == eq::AUTO )
		{
			format.setDepth( true );
			const int depthBits = ( depthSize > 0 ? depthSize : 8 );
			format.setDepthBufferSize( depthBits );
		}

		const int stencilSize = getIAttribute( eq::Window::IATTR_PLANES_STENCIL );
		if( stencilSize > 0 || stencilSize == eq::AUTO )
		{
			format.setStencil( true );
			const int stencilBits = ( stencilSize > 0 ? stencilSize : 1 );
			format.setStencilBufferSize( stencilBits );
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

		const int samplesSize  = getIAttribute( eq::Window::IATTR_PLANES_SAMPLES );
		if( samplesSize >= 0 )
		{
			format.setSampleBuffers( true );
			format.setSamples( samplesSize );
			//TODO is there a way to check if multisampling is actually available?
		}

		if( getIAttribute( eq::Window::IATTR_HINT_STEREO ) == eq::ON ||
			( getIAttribute( eq::Window::IATTR_HINT_STEREO )   == eq::AUTO && 
			  getIAttribute( eq::Window::IATTR_HINT_DRAWABLE ) == eq::WINDOW ) )
		{
			format.setStereo( true );
		}

		if( getIAttribute( eq::Window::IATTR_HINT_DOUBLEBUFFER ) == eq::ON ||
			( getIAttribute( eq::Window::IATTR_HINT_DOUBLEBUFFER ) == eq::AUTO && 
			  getIAttribute( eq::Window::IATTR_HINT_DRAWABLE )     == eq::WINDOW ) )
		{
			format.setDoubleBuffer( true );
		}

		if( getIAttribute( eq::Window::IATTR_HINT_DRAWABLE ) != eq::WINDOW ) {
			EQWARN << "Unsupported drawable type " << getIAttribute( eq::Window::IATTR_HINT_DRAWABLE )
				   << "for QtWindow, creating a window" << std::endl;
		}

		if( !createContext( format ) )
			return false;

		return true;
	}

	void QtWindow::configExit()
	{
	}

	void QtWindow::makeCurrent() const
	{
		EQASSERT( m_pContext && m_pContext->isValid() );

		m_pContext->makeCurrent();
	}

	void QtWindow::swapBuffers()
	{
		EQASSERT( m_pContext && m_pContext->isValid() );

		m_pContext->swapBuffers();
	}

	void QtWindow::joinNVSwapBarrier( const uint32_t group, const uint32_t barrier )
	{
		if( group == 0 && barrier == 0 )
			return;

		//TODO implement this?
		EQWARN << "NV Swap group extension not supported for Qt windows" << endl;
		return;
	}

	bool QtWindow::createContext( const QGLFormat& format )
	{
		EQASSERT( !m_pContext );

		m_pContext = new QGLContext( format );

		QWaitCondition* pWaitCondition = new QWaitCondition();
		QtGLContextRequestEvent* pEvent = new QtGLContextRequestEvent( this, m_pContext, pWaitCondition );

		QMutex mutex;
		mutex.lock();
		qApp->postEvent( QtGLContextCreator::getInstance(), pEvent );
		pWaitCondition->wait( &mutex );
		mutex.unlock();

		delete pWaitCondition;

		return m_pContext->isValid();
	}
}