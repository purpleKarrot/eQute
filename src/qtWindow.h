
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

#ifndef EQQT_QTWINDOW_H
#define EQQT_QTWINDOW_H


#include <eq/client/osWindow.h>

class QGLContext;
class QGLFormat;


namespace eqQt
{
	class QtGLWidget;

	// The interface defining the minimum functionality for a Qt window.
	class QtWindowIF : public eq::OSWindow
	{
	public:
		QtWindowIF( eq::Window* pParent ) : OSWindow( pParent ) {}
		virtual ~QtWindowIF() {}

		virtual const QGLContext* getQGLContext() const = 0;

		virtual bool processEvent( const eq::Event& event ) { return _window->processEvent( event ); }
	};

	// Default implementation of a Qt window
	class QtWindow : public QtWindowIF
	{
	public:
		QtWindow( eq::Window* pParent );
		virtual ~QtWindow();

		virtual bool configInit();
		virtual void configExit();

		virtual void makeCurrent() const;
		virtual void swapBuffers();

		virtual void joinNVSwapBarrier( const uint32_t group, const uint32_t barrier );

		virtual const QGLContext* getQGLContext() const { return m_pContext; }

	protected:
		virtual bool createContext( const QGLFormat& format );

		QGLContext*		m_pContext;
	};
}


#endif // EQQT_QTWINDOW_H
