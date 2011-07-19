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

#include "qtGLContextCreator.h"

#include "qtGLContextRequestEvent.h"

namespace eqQt
{

QtGLContextCreator* QtGLContextCreator::ms_pInstance = 0;

QtGLContextCreator::QtGLContextCreator()
{
	Q_ASSERT_X(!QtGLContextCreator::ms_pInstance, "QtGLContextCreator", "there should be only one instance");

	QtGLContextCreator::ms_pInstance = this;
}

bool QtGLContextCreator::event(QEvent* pEvent)
{
	if (pEvent->type() == QtGLContextRequestEvent::QtGLContextRequest)
	{
		QtGLContextRequestEvent* pContextEvent = (QtGLContextRequestEvent*) pEvent;

		contextRequestEvent(pContextEvent);

		//TODO check if successful?
		pContextEvent->contextFinished();

		return true;
	}
	else
	{
		return QObject::event(pEvent);
	}
}

} // namespace eqQt
