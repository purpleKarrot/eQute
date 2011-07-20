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
class QtWindowListener
{
public:
	virtual void beforeConfigInit()
	{
	}

	virtual void afterConfigInit(bool success)
	{
	}

	virtual void beforeConfigExit()
	{
	}

	virtual void afterConfigExit()
	{
	}

	virtual void beforeMakeCurrent() const
	{
	}

	virtual void afterMakeCurrent() const
	{
	}

	virtual void beforeSwapBuffers()
	{
	}

	virtual void afterSwapBuffers()
	{
	}

	// no fbo support (yet?), so we don't need this:
	//virtual void beforeBindFrameBuffer() const {};
	//virtual void afterBindFrameBuffer() const {};
};

} // namespace eqQt

#endif // EQQT_QTWINDOWLISTENER_H
