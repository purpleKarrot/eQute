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

class QtWindow: public eq::GLWindow
{
public:
	QtWindow(eq::Window* parent) :
			GLWindow(parent), m_pContext(0), m_pWidget(0)
	{
	}

	virtual ~QtWindow()
	{
	}

	bool configInit();
	void configExit();

	void makeCurrent() const;
	void swapBuffers();

	void joinNVSwapBarrier(const uint32_t group, const uint32_t barrier);

	QGLContext* getQGLContext()
	{
		return m_pContext;
	}

	const QGLContext* getQGLContext() const
	{
		return m_pContext;
	}

	void setQtGLWidget(QtGLWidget* pWidget)
	{
		m_pWidget = pWidget;
	}

	QtGLWidget* getQtGLWidget()
	{
		return m_pWidget;
	}

	const QtGLWidget* getQtGLWidget() const
	{
		return m_pWidget;
	}

	QtGLWidget* getShareQtGLWidget();
	const QtGLWidget* getShareQtGLWidget() const;

	// eq Event handling: forward to Window
	virtual bool processEvent(const eq::Event& event)
	{
		return this->getWindow()->processEvent(event);
	}

	// add/remove listeners
	bool registerListener(QtWindowListener* pListener);
	bool unregisterListener(QtWindowListener* pListener);
	void unregisterAllListeners();

protected:
	bool configInitImpl();
	void configExitImpl();

	void makeCurrentImpl() const;
	void swapBuffersImpl();

	bool createContext(const QGLFormat& format);

private:
	void notifyListenersBeforeConfigExit();
	void notifyListenersAfterConfigExit();

	typedef std::set<QtWindowListener*> ListenerSet;
	ListenerSet m_listeners;
	mutable QMutex m_listenersMutex;

protected:
	QGLContext* m_pContext;
	QtGLWidget* m_pWidget;
};

} // namespace eqQt

#endif // EQQT_QTWINDOW_H
