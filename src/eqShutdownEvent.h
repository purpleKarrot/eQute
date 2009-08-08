
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

#ifndef EQQT_EQSHUTDOWNEVENT_H
#define EQQT_EQSHUTDOWNEVENT_H


#include <QtCore/QEvent>

class QGLContext;
class QWaitCondition;


namespace eqQt
{
	// Custom Qt event, to be sent when Equalizer is shutting down
	// (i.e. configExit is called).
	class EqShutdownEvent : public QEvent
	{
	public:
		enum Type
		{
			EqShutdown = QEvent::User + 10001
		};

		EqShutdownEvent();
	};
}


#endif EQQT_EQSHUTDOWNEVENT_H
