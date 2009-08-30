
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

#ifndef WINDOW_H
#define WINDOW_H


#include <eq/client/window.h>

#include "qtWindow.h"


class Window : public eq::Window
{
public:
	Window( eq::Pipe* pParent ) : eq::Window( pParent ), m_pQtWindow( 0 ) {}

	//eqQt::QtWindowIF* getQtWindow() { return m_pQtWindow; }

protected:
	virtual bool configInitOSWindow( const uint32_t initID );

private:
	eqQt::QtWindowIF* m_pQtWindow;
};


#endif // WINDOW_H
