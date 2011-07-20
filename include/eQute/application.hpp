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

#ifndef EQUTE_APPLICATION_HPP
#define EQUTE_APPLICATION_HPP

#include <eq/client/nodeFactory.h>
#include "pimpl.hpp"

namespace eQute
{

struct Application: eq::NodeFactory, pimpl<Application>::pointer_semantics
{
	Application(int argc, char* argv[]);

	virtual ~Application();
};

} // namespace eQute

#endif /* EQUTE_APPLICATION_HPP */
