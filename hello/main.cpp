
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

#include <QtGui/QApplication>

#include "applicationThread.h"
#include "contextCreator.h"


int main(int argc, char *argv[])
{
	// create the QApplication
	QApplication q( argc, argv );

	// create the ContextCreator
	ContextCreator cc;

	// create & start the equalizer thread
	ApplicationThread appThread( argc, argv );
	appThread.start();

	// run Qt event loop
	int result = q.exec();

	// wait for equalizer to finish
	void* pAppThreadReturn;
	appThread.join( &pAppThreadReturn );
	result += ( int )pAppThreadReturn; // hrm..

	return result;
}
