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

#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <QObject>
#include <boost/thread/thread.hpp>
#include <eq/client/nodeFactory.h>

namespace eQute
{

struct ApplicationImpl: QObject
{
	Q_OBJECT

public:
	ApplicationImpl(int argc, char* argv[], eq::NodeFactory* nodeFactory);

private:
	void run(int argc, char* argv[], eq::NodeFactory* nodeFactory);

private slots:
	void stop();

private:
	boost::thread thread;
};

} // namespace eQute

#endif /* APPLICATION_HPP */
