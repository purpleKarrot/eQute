/* Copyright (c) 2011, Daniel Pfeifer <daniel@pfeifer-mail.de>
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

#ifndef PIPE_HPP
#define PIPE_HPP

#include <QGLWidget>
#include <eq/client/systemPipe.h>

namespace eQute
{

class Pipe: public eq::SystemPipe, public QGLWidget
{
public:
	Pipe(eq::Pipe* parent) :
			eq::SystemPipe(parent), QGLWidget(QGLFormat::defaultFormat())
	{
	}

	virtual ~Pipe()
	{
	}

private:
	bool configInit()
	{
		return true;
	}

	void configExit()
	{
	}
};

} // namespace eQute

#endif /* PIPE_HPP */
