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

#include "qtGLContextRequestEvent.h"

#include <QtCore/QWaitCondition>

namespace eqQt
{

QtGLContextRequestEvent::QtGLContextRequestEvent(QtWindow* window, QWaitCondition* pNotify) :
		QEvent((QEvent::Type) QtGLContextRequest), m_pQtWindow(window), m_pNotify(pNotify)
{
}

void QtGLContextRequestEvent::contextFinished()
{
	m_pNotify->wakeAll();
}

} // namespace eqQt
