
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

#include "window.h"

#include "qtWindow.h"


bool Window_::configInitOSWindow( const uint32_t initID )
{
	m_pQtWindow = new eqQt::QtWindow( this );

	if( !m_pQtWindow->configInit() )
	{
		EQWARN << "OS Window initialization failed" << std::endl;
		delete m_pQtWindow;
		return false;
	}

	setSystemWindow( m_pQtWindow );

	return true;
}
