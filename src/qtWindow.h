
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


#include <set>

#include <eq/client/glWindow.h>

#include <QtCore/QMutex>

#include "qtWindowListener.h"

class QGLContext;
class QGLFormat;


namespace eqQt
{
	class QtGLWidget;

	// The interface defining the minimum functionality for a Qt window.
	// Also provides an interface to register listeners to the window state.
	// Listeners are notified automatically before and after each eq task method.
	// Subclasses must implement the "Impl" methods instead of the normal eq task methods,
	// e.g. configInitImpl instead of configInit.
	class QtWindowIF : public eq::GLWindow
	{
	public:
		QtWindowIF( eq::Window* pParent ) : GLWindow( pParent ) {};
		virtual ~QtWindowIF() {}

		// eq task methods are non-virtual here,
		// implement the "Impl" variants instead!
		bool configInit();
		void configExit();

		void makeCurrent() const;
		void swapBuffers();

		// QGLContext access
		virtual       QGLContext* getQGLContext() = 0;
		virtual const QGLContext* getQGLContext() const = 0;

		// QtGLWidget access
		virtual void              setQtGLWidget( QtGLWidget* pWidget ) = 0;
		virtual       QtGLWidget* getQtGLWidget() = 0;
		virtual const QtGLWidget* getQtGLWidget() const = 0;
		virtual       QtGLWidget* getShareQtGLWidget() = 0;
		virtual const QtGLWidget* getShareQtGLWidget() const = 0;

		// eq Event handling: forward to Window
		virtual bool processEvent( const eq::Event& event ) { return _window->processEvent( event ); }

		// add/remove listeners
		bool registerListener( QtWindowListener* pListener );
		bool unregisterListener( QtWindowListener* pListener );
		void unregisterAllListeners();

	protected:
		// implementations of eq task methods
		virtual bool configInitImpl() = 0;
		virtual void configExitImpl() = 0;

		virtual void makeCurrentImpl() const;
		virtual void swapBuffersImpl() = 0;

	private:
		void notifyListenersBeforeConfigInit();
		void notifyListenersAfterConfigInit( bool success );
		void notifyListenersBeforeConfigExit();
		void notifyListenersAfterConfigExit();
        void notifyListenersBeforeMakeCurrent() const;
        void notifyListenersAfterMakeCurrent() const;
        void notifyListenersBeforeSwapBuffers();
        void notifyListenersAfterSwapBuffers();

		typedef std::set< QtWindowListener* > ListenerSet;
		ListenerSet			m_listeners;
		mutable QMutex		m_listenersMutex;
	};

	// Default implementation of a Qt window
	class QtWindow : public QtWindowIF
	{
	public:
		QtWindow( eq::Window* pParent );
		virtual ~QtWindow();

		virtual void joinNVSwapBarrier( const uint32_t group, const uint32_t barrier );

		virtual       QGLContext* getQGLContext()       { return m_pContext; }
		virtual const QGLContext* getQGLContext() const { return m_pContext; }

		virtual void              setQtGLWidget( QtGLWidget* pWidget ) { m_pWidget = pWidget; }
		virtual       QtGLWidget* getQtGLWidget()       { return m_pWidget; }
		virtual const QtGLWidget* getQtGLWidget() const { return m_pWidget; }
		virtual       QtGLWidget* getShareQtGLWidget();
		virtual const QtGLWidget* getShareQtGLWidget() const;

	protected:
		virtual bool configInitImpl();
		virtual void configExitImpl();

		virtual void makeCurrentImpl() const;
		virtual void swapBuffersImpl();

		virtual bool createContext( const QGLFormat& format );

	private:
		QGLContext*		m_pContext;
		QtGLWidget*		m_pWidget;
	};
}


#endif // EQQT_QTWINDOW_H
