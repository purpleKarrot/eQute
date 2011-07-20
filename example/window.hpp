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

template<typename SystemWindow>
struct Window_: eq::Window
{
	Window_(eq::Pipe* parent) :
			eq::Window(parent)
	{
	}

	bool configInitSystemWindow(const eq::uint128_t&)
	{
		SystemWindow* system_window = new SystemWindow(this);

		if (!system_window->configInit())
		{
			EQWARN << "SystemWindow initialization failed" << std::endl;
			delete system_window;
			return false;
		}

		setSystemWindow(system_window);
		return true;
	}
};

#endif // WINDOW_H
