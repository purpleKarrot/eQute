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

#include <eQute/application.hpp>

#include <QApplication>
#include <boost/thread/thread.hpp>

#include <eq/client/init.h>
#include <eq/client/config.h>
#include <eq/client/client.h>
#include <eq/client/server.h>
#include <eq/client/configParams.h>

#include "application.hpp"

template<>
struct pimpl<eQute::Application>::implementation: eQute::ApplicationImpl
{
	implementation(int argc, char* argv[], eq::NodeFactory* nodeFactory) :
			eQute::ApplicationImpl(argc, argv, nodeFactory)
	{
	}
};

namespace eQute
{

Application::Application(int argc, char* argv[]) :
		base(argc, argv, this)
{
}

Application::~Application()
{
}

ApplicationImpl::ApplicationImpl(int argc, char* argv[], eq::NodeFactory* nodeFactory) :
		thread(&ApplicationImpl::run, this, argc, argv, nodeFactory)
{
	QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(stop()));
}

void ApplicationImpl::run(int argc, char* argv[], eq::NodeFactory* nodeFactory)
{
	if (!eq::init(argc, argv, nodeFactory))
	{
		EQERROR << "Equalizer init failed" << std::endl;
		return;
	}

	eq::ClientPtr client = new eq::Client();
	if (!client->initLocal(argc, argv))
	{
		EQERROR << "Can't init client" << std::endl;
		eq::exit();
		return;
	}

	eq::ServerPtr server = new eq::Server();
	if (!client->connectServer(server))
	{
		EQERROR << "Can't open server" << std::endl;
		client->exitLocal();
		eq::exit();
		return;
	}

	eq::ConfigParams config_params;
	eq::Config* config = server->chooseConfig(config_params);

	if (!config)
	{
		EQERROR << "No matching config on server" << std::endl;
		client->disconnectServer(server);
		client->exitLocal();
		eq::exit();
		return;
	}

	uint32_t spin = 0;

	if (!config->init(spin))
	{
		EQERROR << "Config initialization failed! " << std::endl;
		server->releaseConfig(config);
		config->exit();
		client->disconnectServer(server);
		client->exitLocal();
		eq::exit();
		return;
	}

	while (config->isRunning())
	{
		config->startFrame(++spin);
		config->finishFrame();
	}

	config->finishAllFrames();
	config->exit();
	server->releaseConfig(config);
	client->disconnectServer(server);
	client->exitLocal();

	eq::exit();
}

void ApplicationImpl::stop()
{
	thread.join();
}

} // namespace eQute
