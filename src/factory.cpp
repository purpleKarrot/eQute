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

#include <QApplication>
#include <QDesktopWidget>
#include <co/base/monitor.h>
#include <eq/fabric/pixelViewport.h>
#include <eq/fabric/gpuInfo.h>
#include <eq/client/windowSystem.h>

#include <boost/foreach.hpp>

#include "pipe.hpp"

namespace eQute
{

typedef co::base::Monitor<eq::SystemWindow*> WindowMonitor;
typedef co::base::Monitor<eq::SystemPipe*> PipeMonitor;
//typedef co::base::Monitor<eq::MessagePump*> PumpMonitor;

static const QEvent::Type WindowEnum = QEvent::Type(QEvent::User + 1);
static const QEvent::Type PipeEnum = QEvent::Type(QEvent::User + 2);
//static const QEvent::Type PumpEnum = QEvent::Type(QEvent::User + 3);

struct WindowEvent: QEvent
{
	WindowEvent(WindowMonitor& monitor, eq::Window* window) :
			QEvent(WindowEnum), monitor(monitor), window(window)
	{
	}

	WindowMonitor& monitor;
	eq::Window* window;
};

struct PipeEvent: QEvent
{
	PipeEvent(PipeMonitor& monitor, eq::Pipe* pipe) :
			QEvent(PipeEnum), monitor(monitor), pipe(pipe)
	{
	}

	PipeMonitor& monitor;
	eq::Pipe* pipe;
};

//struct PumpEvent: QEvent
//{
//	PumpEvent(PumpMonitor& monitor) :
//			QEvent(PumpEnum), monitor(monitor)
//	{
//	}
//
//	PumpMonitor& monitor;
//};

// SystemWindow and SystemPipe are created in the main thread.
static class : QObject, eq::WindowSystemIF
{
	std::string getName() const
	{
		return "Qt";
	}

	eq::SystemWindow* createWindow(eq::Window* window) const
	{
		return 0;
//		WindowMonitor monitor;
//		qApp->postEvent((QObject*) this, new WindowEvent(monitor, window));
//		return monitor.waitNE(0);
	}

	eq::SystemPipe* createPipe(eq::Pipe* pipe) const
	{
		PipeMonitor monitor;
		qApp->postEvent((QObject*) this, new PipeEvent(monitor, pipe));
		return monitor.waitNE(0);
	}

	eq::MessagePump* createMessagePump() const
	{
		return 0;
//		PumpMonitor monitor;
//		qApp->postEvent((QObject*) this, new PumpEvent(monitor));
//		return monitor.waitNE(0);
	}

	eq::GPUInfos discoverGPUs() const
	{
		eq::GPUInfos gpu_infos;
//		QDesktopWidget* desktop = qApp->desktop();
//		eq::GPUInfos gpu_infos(desktop->screenCount());
//
//		for (std::size_t i = 0; i < desktop->screenCount(); ++i)
//		{
//			eq::fabric::GPUInfo& info = gpu_infos[i];
//
//			info.port = 0;
//			info.device = 1;
//
//			QRect rect = desktop->availableGeometry(i);
//			info.pvp.x = rect.x();
//			info.pvp.y = rect.y();
//			info.pvp.h = rect.width();
//			info.pvp.w = rect.height();
//		}

		return gpu_infos;
	}

	bool event(QEvent* e)
	{
		switch (e->type())
		{
		case WindowEnum:
		{
//			static_cast<WindowEvent*>(e)->monitor.set(new eq::SystemWindow);
//			return true;
		}
		case PipeEnum:
		{
			PipeEvent* pipe_event = static_cast<PipeEvent*>(e);
			pipe_event->monitor.set(new Pipe(pipe_event->pipe));
			return true;
		}
//		case PumpEnum:
//		{
//			static_cast<PumpEvent*>(e)->monitor.set(new eq::MessagePump);
//			return true;
//		}
		default:
			return QObject::event(e);
		}
	}

} _factory;

} // namespace eQute
