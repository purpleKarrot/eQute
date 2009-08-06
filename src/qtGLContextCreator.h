
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

#ifndef EQQT_QTGLWIDGETREQUESTQUEUE_H
#define EQQT_QTGLWIDGETREQUESTQUEUE_H


#include <deque>
#include <set>

#include <QtCore/QMutex>
#include <QtCore/QObject>
#include <QtCore/QWaitCondition>

class QEvent;


namespace eqQt
{
	class QtGLContextRequestEvent;

	// Helper class to create QGLContexts in the main (Qt gui) thread.
	// This is necessary because a QGLContext needs a QGLWidget, which
	// may only be created by the main thread.
	// Has to be subclassed by an application-specific class that implements
	// the actual contextRequestEvent function.
	class QtGLContextCreator : public QObject
	{
		Q_OBJECT

	public:
		QtGLContextCreator();

		static QtGLContextCreator* getInstance() { return ms_pInstance; }

		virtual bool event( QEvent* pEvent );

	protected:
		virtual void contextRequestEvent( QtGLContextRequestEvent* pEvent ) = 0;

	private:
		static QtGLContextCreator* ms_pInstance;
	};
}


#endif // EQQT_QTGLWIDGETREQUESTQUEUE_H
