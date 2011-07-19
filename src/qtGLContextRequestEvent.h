
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

#ifndef EQQT_QTGLCONTEXTEVENT_H
#define EQQT_QTGLCONTEXTEVENT_H


#include <QtCore/QEvent>

class QGLContext;
class QWaitCondition;


namespace eqQt
{
	class QtGLContext;
	class QtWindowIF;

	// Custom Qt event encapsulating a request for a Qt context.
	// This is created by the QtWindows and posted to the QtGLContextCreator,
	// where it will be handled by the main thread.
	class QtGLContextRequestEvent : public QEvent
	{
	public:
		enum Type
		{
			QtGLContextRequest = QEvent::User + 10000
		};

		QtGLContextRequestEvent( QtWindowIF* pQtWindow, QWaitCondition* pNotify );

		QtWindowIF*		getQtWindow() { return m_pQtWindow; }

		void			contextFinished();

	private:
		QtWindowIF*		m_pQtWindow;
		QWaitCondition*	m_pNotify;
	};
}


#endif /* EQQT_QTGLCONTEXTEVENT_H */
