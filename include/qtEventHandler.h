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

#ifndef EQQT_QTEVENTHANDLER_H
#define EQQT_QTEVENTHANDLER_H

#include <eq/client/event.h>
#include <eq/client/eventHandler.h>

#include <QtGui/QMouseEvent>

class QMouseEvent;
class QKeyEvent;
class QMoveEvent;
class QResizeEvent;
class QShowEvent;
class QHideEvent;
class QCloseEvent;

namespace eqQt
{

class QtWindow;

// Implementation of an eq::EventHandler for Qt events.
// Mostly translates the QEvents it receives into eq::Events
// and forwards them to the QtWindowIF.
class QtEventHandler: public eq::EventHandler
{
public:
	QtEventHandler(QtWindow* window);
	virtual ~QtEventHandler();

	void mousePressEvent(QWidget* pSender, QMouseEvent* pEvent);
	void mouseReleaseEvent(QWidget* pSender, QMouseEvent* pEvent);
	void mouseMoveEvent(QWidget* pSender, QMouseEvent* pEvent);

	void keyPressEvent(QWidget* pSender, QKeyEvent* pEvent);
	void keyReleaseEvent(QWidget* pSender, QKeyEvent* pEvent);

	void paintEvent(QWidget* pSender, QPaintEvent* pEvent);
	void moveEvent(QWidget* pSender, QMoveEvent* pEvent);
	void resizeEvent(QWidget* pSender, QResizeEvent* pEvent);
	void showEvent(QWidget* pSender, QShowEvent* pEvent);
	void hideEvent(QWidget* pSender, QHideEvent* pEvent);
	void closeEvent(QWidget* pSender, QCloseEvent* pEvent);

	void setQtWindow(QtWindow* window)
	{
		m_pQtWindow = window;
	}

protected:
	static uint32_t convertQtButtonToEqButton(Qt::MouseButton qtButton);
	static uint32_t convertQtButtonsToEqButtons(Qt::MouseButtons qtButtons);

	static uint32_t convertQtKeyToEqKey(QKeyEvent* pEvent);

	void fillOriginatorID(eq::Event& eqEvent);
	void fillRenderContext(eq::Event& eqEvent);

private:
	QtWindow* m_pQtWindow;
};

} // namespace eqQt

#endif // EQQT_QTEVENTHANDLER_H
