
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

#include "applicationThread.h"

#include "application.h"
#include "channel.h"
#include "window.h"


class NodeFactory : public eq::NodeFactory
{
public:
	virtual eq::Window*	 createWindow(  eq::Pipe*   pParent ) { return new Window(  pParent ); }
	virtual eq::Channel* createChannel( eq::Window* pParent ) { return new Channel( pParent ); }
};

ApplicationThread::ApplicationThread( int argc, char** argv )
	: m_argc( argc ), m_argv( argv )
{
}

void* ApplicationThread::run()
{
	// 1. Equalizer initialization
	NodeFactory nodeFactory;
	if( !eq::init( m_argc, m_argv, &nodeFactory ) ) {
		EQERROR << "Equalizer init failed" << std::endl;
		return ( void* )EXIT_FAILURE;
	}

	// 2. initialization of local client node
	eq::base::RefPtr< Application > client = new Application();
	if( !client->initLocal( m_argc, m_argv ) ) {
		EQERROR << "Can't init client" << std::endl;
		eq::exit();
		return ( void* )EXIT_FAILURE;
	}

	// 3. run client
	int returnValue = client->run();

	// 4. cleanup and exit
	client->exitLocal();
	client = 0;

	eq::exit();

	return ( void* )returnValue;
}
