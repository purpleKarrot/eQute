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

#ifndef EQQT_QTWINDOWLISTENER_H
#define EQQT_QTWINDOWLISTENER_H

namespace eqQt
{

// Interface for listeners to the state of a QtWindow.
// Listeners are notified before and after the execution of each
// eq task method.
struct QtWindowListener
{
	virtual void beforeConfigExit() = 0;
	virtual void afterConfigExit() = 0;
};

} // namespace eqQt

#endif // EQQT_QTWINDOWLISTENER_H
