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

#include "application.h"

#include <eq/client/config.h>

int Application::run()
{
	// 1. connect to server
	eq::ServerPtr pServer = new eq::Server();
	if (!connectServer(pServer))
	{
		EQERROR << "Can't open server" << std::endl;
		return EXIT_FAILURE;
	}

	// 2. choose config
	eq::ConfigParams configParams;
	eq::Config* pConfig = pServer->chooseConfig(configParams);

	if (!pConfig)
	{
		EQERROR << "No matching config on server" << std::endl;
		disconnectServer(pServer);
		return EXIT_FAILURE;
	}

	uint32_t spin = 0;

	// 3. init config
	if (!pConfig->init(spin))
	{
		EQERROR << "Config initialization failed! " << std::endl;
		pServer->releaseConfig(pConfig);
		disconnectServer(pServer);
		return EXIT_FAILURE;
	}

	// 4. run main loop
	while (pConfig->isRunning())
	{
		pConfig->startFrame(++spin);
		pConfig->finishFrame();
	}
	const uint32_t frame = pConfig->finishAllFrames();

	// 5. exit config
	pConfig->exit();

	// 6. cleanup and exit
	pServer->releaseConfig(pConfig);
	if (!disconnectServer(pServer))
		EQERROR << "Client::disconnectServer failed" << std::endl;
	pServer = 0;

	return EXIT_SUCCESS;
}
