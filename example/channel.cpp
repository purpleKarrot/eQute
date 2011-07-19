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

#include "channel.h"

Channel::Channel(eq::Window* pParent) :
		eq::Channel(pParent)
{
}

void Channel::frameDraw(const uint32_t spin)
{
	// setup OpenGL State
	eq::Channel::frameDraw(spin);

	const float lightPos[] = { 0.0f, 0.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);

	const float lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);

	// rotate scene around the origin
	glRotatef(static_cast<float>(spin) * 0.1f, 1.0f, 0.5f, 0.25f);

	// render six axis-aligned colored quads around the origin
	//  front
	glColor3f(1.0f, 0.5f, 0.5f);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(.7f, .7f, -1.0f);
	glVertex3f(-.7f, .7f, -1.0f);
	glVertex3f(.7f, -.7f, -1.0f);
	glVertex3f(-.7f, -.7f, -1.0f);
	glEnd();

	//  bottom
	glColor3f(0.5f, 1.0f, 0.5f);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(.7f, -1.0f, .7f);
	glVertex3f(-.7f, -1.0f, .7f);
	glVertex3f(.7f, -1.0f, -.7f);
	glVertex3f(-.7f, -1.0f, -.7f);
	glEnd();

	//  back
	glColor3f(0.5f, 0.5f, 1.0f);
	glNormal3f(0.0f, 0.0f, -1.0f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(.7f, .7f, 1.0f);
	glVertex3f(-.7f, .7f, 1.0f);
	glVertex3f(.7f, -.7f, 1.0f);
	glVertex3f(-.7f, -.7f, 1.0f);
	glEnd();

	//  top
	glColor3f(1.0f, 1.0f, 0.5f);
	glNormal3f(0.f, -1.f, 0.f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(.7f, 1.0f, .7f);
	glVertex3f(-.7f, 1.0f, .7f);
	glVertex3f(.7f, 1.0f, -.7f);
	glVertex3f(-.7f, 1.0f, -.7f);
	glEnd();

	//  right
	glColor3f(1.0f, 0.5f, 1.0f);
	glNormal3f(-1.f, 0.f, 0.f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(1.0f, .7f, .7f);
	glVertex3f(1.0f, -.7f, .7f);
	glVertex3f(1.0f, .7f, -.7f);
	glVertex3f(1.0f, -.7f, -.7f);
	glEnd();

	//  left
	glColor3f(0.5f, 1.0f, 1.0f);
	glNormal3f(1.f, 0.f, 0.f);
	glBegin(GL_TRIANGLE_STRIP);
	glVertex3f(-1.0f, .7f, .7f);
	glVertex3f(-1.0f, -.7f, .7f);
	glVertex3f(-1.0f, .7f, -.7f);
	glVertex3f(-1.0f, -.7f, -.7f);
	glEnd();

}
