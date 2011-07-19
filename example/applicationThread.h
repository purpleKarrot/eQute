
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

#ifndef APPLICATIONTHREAD_H
#define APPLICATIONTHREAD_H


#include <co/base/thread.h>


class ApplicationThread : public co::base::Thread
{
public:
	ApplicationThread( int argc, char** argv );

	void run();

private:
	int			m_argc;
	char**		m_argv;
};


#endif // APPLICATIONTHREAD_H
