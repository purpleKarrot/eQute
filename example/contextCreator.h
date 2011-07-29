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

#ifndef CONTEXTCREATOR_H
#define CONTEXTCREATOR_H

#include "qtGLContextCreator.h"

namespace eqQt
{
class QtGLContextRequestEvent;
}

class ContextCreator: public eqQt::QtGLContextCreator
{
public:
	virtual ~ContextCreator()
	{
	}

private:
	void contextRequestEvent(eqQt::QtGLContextRequestEvent* pEvent);
};

#endif // CONTEXTCREATOR_H
