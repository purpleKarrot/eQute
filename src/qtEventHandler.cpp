
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

#include "qtEventHandler.h"

#include <QtCore/QPoint>
#include <QtCore/QSize>
#include <QtGui/QWidget>
#include <QtGui/QMoveEvent>
#include <QtGui/QResizeEvent>
#include <QtGui/QShowEvent>
#include <QtGui/QHideEvent>
#include <QtGui/QCloseEvent>

#include "qtWindow.h"


namespace eqQt
{
	QtEventHandler::QtEventHandler( QtWindowIF* pQtWindow )
		: m_pQtWindow( pQtWindow )
	{
	}

	QtEventHandler::~QtEventHandler()
	{
	}

	void QtEventHandler::mousePressEvent( QWidget* pSender, QMouseEvent* pEvent )
	{
		if( !m_pQtWindow )
			return;

		// translate to eq::Event
		eq::Event eqEvent;
		eqEvent.type = eq::Event::POINTER_BUTTON_PRESS;
		eqEvent.pointerButtonPress.button = convertQtButtonToEqButton( pEvent->button() );
		eqEvent.pointerButtonPress.buttons = convertQtButtonsToEqButtons( pEvent->buttons() );

		//TODO do this recursively, until we reach the screen?
		QPoint posInParent;
		if( pSender->isTopLevel() )
			posInParent = pEvent->pos();
		else
			posInParent = pSender->mapToParent( pEvent->pos() );

		eqEvent.pointerButtonPress.x = posInParent.x();
		eqEvent.pointerButtonPress.y = posInParent.y();

		_computePointerDelta( m_pQtWindow->getWindow(), eqEvent );

		fillOriginatorID( eqEvent );
		fillRenderContext( eqEvent );

		m_pQtWindow->processEvent( eqEvent );

		pEvent->accept();
	}

	void QtEventHandler::mouseReleaseEvent( QWidget* pSender, QMouseEvent* pEvent )
	{
		if( !m_pQtWindow )
			return;

		// translate to eq::Event
		eq::Event eqEvent;
		eqEvent.type = eq::Event::POINTER_BUTTON_RELEASE;
		eqEvent.pointerButtonPress.button = convertQtButtonToEqButton( pEvent->button() );
		eqEvent.pointerButtonPress.buttons = convertQtButtonsToEqButtons( pEvent->buttons() );

		//TODO do this recursively, until we reach the screen?
		QPoint posInParent;
		if( pSender->isTopLevel() )
			posInParent = pEvent->pos();
		else
			posInParent = pSender->mapToParent( pEvent->pos() );

		eqEvent.pointerButtonPress.x = posInParent.x();
		eqEvent.pointerButtonPress.y = posInParent.y();

		_computePointerDelta( m_pQtWindow->getWindow(), eqEvent );

		fillOriginatorID( eqEvent );
		fillRenderContext( eqEvent );

		m_pQtWindow->processEvent( eqEvent );
	}

	void QtEventHandler::mouseMoveEvent( QWidget* pSender, QMouseEvent* pEvent )
	{
		if( !m_pQtWindow )
			return;

		// translate to eq::Event
		eq::Event eqEvent;
		eqEvent.type = eq::Event::POINTER_MOTION;
		eqEvent.pointerMotion.buttons = convertQtButtonsToEqButtons( pEvent->buttons() );

		//TODO do this recursively, until we reach the screen?
		QPoint posInParent;
		if( pSender->isTopLevel() )
			posInParent = pEvent->pos();
		else
			posInParent = pSender->mapToParent( pEvent->pos() );

		eqEvent.pointerMotion.x = posInParent.x();
		eqEvent.pointerMotion.y = posInParent.y();

		_computePointerDelta( m_pQtWindow->getWindow(), eqEvent );

		fillOriginatorID( eqEvent );
		fillRenderContext( eqEvent );

		m_pQtWindow->processEvent( eqEvent );
	}

	void QtEventHandler::keyPressEvent( QWidget* pSender, QKeyEvent* pEvent )
	{
		if( !m_pQtWindow )
			return;

		// translate to eq::Event
		eq::Event eqEvent;
		eqEvent.type = eq::Event::KEY_PRESS;
		eqEvent.keyPress.key = convertQtKeyToEqKey( pEvent );

		eqEvent.originator = m_pQtWindow->getWindow()->getID();

		m_pQtWindow->processEvent( eqEvent );
	}

	void QtEventHandler::keyReleaseEvent( QWidget* pSender, QKeyEvent* pEvent )
	{
		if( !m_pQtWindow )
			return;

		// translate to eq::Event
		eq::Event eqEvent;
		eqEvent.type = eq::Event::KEY_RELEASE;
		eqEvent.keyRelease.key = convertQtKeyToEqKey( pEvent );

		eqEvent.originator = m_pQtWindow->getWindow()->getID();

		m_pQtWindow->processEvent( eqEvent );
	}

	void QtEventHandler::moveEvent( QWidget* pSender, QMoveEvent* pEvent )
	{
		if( !m_pQtWindow )
			return;

		// translate to eq::Event
		eq::Event eqEvent;
		eqEvent.type = eq::Event::WINDOW_RESIZE;
		eqEvent.resize.x = pEvent->pos().x();
		eqEvent.resize.y = pEvent->pos().y();
		eqEvent.resize.w = pSender->size().width();
		eqEvent.resize.h = pSender->size().height();

		fillOriginatorID( eqEvent );

		m_pQtWindow->processEvent( eqEvent );
	}

	void QtEventHandler::resizeEvent( QWidget* pSender, QResizeEvent* pEvent )
	{
		if( !m_pQtWindow )
			return;

		// translate to eq::Event
		eq::Event eqEvent;
		eqEvent.type = eq::Event::WINDOW_RESIZE;
		eqEvent.resize.x = pSender->pos().x();
		eqEvent.resize.y = pSender->pos().y();
		eqEvent.resize.w = pEvent->size().width();
		eqEvent.resize.h = pEvent->size().height();

		fillOriginatorID( eqEvent );

		m_pQtWindow->processEvent( eqEvent );
	}

	void QtEventHandler::showEvent( QWidget* pSender, QShowEvent* pEvent )
	{
		if( !m_pQtWindow )
			return;

		// translate to eq::Event
		eq::Event eqEvent;
		eqEvent.type = eq::Event::WINDOW_SHOW;
		eqEvent.resize.x = pSender->pos().x();
		eqEvent.resize.y = pSender->pos().y();
		eqEvent.show.w = pSender->size().width();
		eqEvent.show.h = pSender->size().height();

		fillOriginatorID( eqEvent );

		m_pQtWindow->processEvent( eqEvent );
	}

	void QtEventHandler::hideEvent( QWidget* pSender, QHideEvent* pEvent )
	{
		if( !m_pQtWindow )
			return;

		// translate to eq::Event
		eq::Event eqEvent;
		eqEvent.type = eq::Event::WINDOW_HIDE;

		fillOriginatorID( eqEvent );

		m_pQtWindow->processEvent( eqEvent );
	}

	void QtEventHandler::closeEvent( QWidget* pSender, QCloseEvent* pEvent )
	{
		if( !m_pQtWindow )
			return;

		// translate to eq::Event
		eq::Event eqEvent;
		eqEvent.type = eq::Event::WINDOW_CLOSE;

		fillOriginatorID( eqEvent );

		m_pQtWindow->processEvent( eqEvent );
	}

	uint32_t QtEventHandler::convertQtButtonToEqButton( Qt::MouseButton qtButton )
	{
		switch( qtButton ) {
			case Qt::LeftButton:
				return eq::PTR_BUTTON1;

			case Qt::MidButton:
				return eq::PTR_BUTTON2;

			case Qt::RightButton:
				return eq::PTR_BUTTON3;

			case Qt::XButton1:
				return eq::PTR_BUTTON4;

			case Qt::XButton2:
				return eq::PTR_BUTTON5;

			default:
				return 0;
		}
	}

	uint32_t QtEventHandler::convertQtButtonsToEqButtons( Qt::MouseButtons qtButtons )
	{
		uint32_t result = 0;

		if( qtButtons & Qt::LeftButton )
			result |= eq::PTR_BUTTON1;

		if( qtButtons & Qt::MidButton )
			result |= eq::PTR_BUTTON2;

		if( qtButtons & Qt::RightButton )
			result |= eq::PTR_BUTTON3;

		if( qtButtons & Qt::XButton1 )
			result |= eq::PTR_BUTTON4;

		if( qtButtons & Qt::XButton2 )
			result |= eq::PTR_BUTTON5;

		return result;
	}

	uint32_t QtEventHandler::convertQtKeyToEqKey( QKeyEvent* pEvent )
	{
		// check for special keys
		switch( pEvent->key() ) {
			case Qt::Key_Escape:
				return eq::KC_ESCAPE;

			case Qt::Key_Backspace:
				return eq::KC_BACKSPACE;

			case Qt::Key_Return:
				return eq::KC_RETURN;

			case Qt::Key_Tab:
				return eq::KC_TAB;

			case Qt::Key_Home:
				return eq::KC_HOME;

			case Qt::Key_Left:
				return eq::KC_LEFT;

			case Qt::Key_Up:
				return eq::KC_UP;

			case Qt::Key_Right:
				return eq::KC_RIGHT;

			case Qt::Key_Down:
				return eq::KC_DOWN;

			case Qt::Key_PageUp:
				return eq::KC_PAGE_UP;

			case Qt::Key_PageDown:
				return eq::KC_PAGE_DOWN;

			case Qt::Key_End:
				return eq::KC_END;

			case Qt::Key_F:
				return eq::KC_F1;

			case Qt::Key_F2:
				return eq::KC_F2;

			case Qt::Key_F3:
				return eq::KC_F3;

			case Qt::Key_F4:
				return eq::KC_F4;

			case Qt::Key_F5:
				return eq::KC_F5;

			case Qt::Key_F6:
				return eq::KC_F6;

			case Qt::Key_F7:
				return eq::KC_F7;

			case Qt::Key_F8:
				return eq::KC_F8;

			case Qt::Key_F9:
				return eq::KC_F9;

			case Qt::Key_F10:
				return eq::KC_F10;

			case Qt::Key_F11:
				return eq::KC_F11;

			case Qt::Key_F12:
				return eq::KC_F12;

			case Qt::Key_F13:
				return eq::KC_F13;

			case Qt::Key_F14:
				return eq::KC_F14;

			case Qt::Key_F15:
				return eq::KC_F15;

			case Qt::Key_F16:
				return eq::KC_F16;

			case Qt::Key_F17:
				return eq::KC_F17;

			case Qt::Key_F18:
				return eq::KC_F18;

			case Qt::Key_F19:
				return eq::KC_F19;

			case Qt::Key_F20:
				return eq::KC_F20;

			case Qt::Key_F21:
				return eq::KC_F21;

			case Qt::Key_F22:
				return eq::KC_F22;

			case Qt::Key_F23:
				return eq::KC_F23;

			case Qt::Key_F24:
				return eq::KC_F24;

			case Qt::Key_Shift:
				//TODO distinguish between left/right shift
				return eq::KC_SHIFT_L;
				//return eq::KC_SHIFT_R;

			case Qt::Key_Control:
				//TODO ^^ditto
				return eq::KC_CONTROL_L;
				//return eq::KC_CONTROL_R;

			case Qt::Key_Alt:
				return eq::KC_ALT_L;

			case Qt::Key_AltGr:
				// report AltGr as right alt
				return eq::KC_ALT_R;

			case Qt::Key_unknown:
				return eq::KC_VOID;
		}

		// still here -> no special key

		// is there a key value?
		if( pEvent->text().isEmpty() ) {
			// no key value, don't know key
			return eq::KC_VOID;
		}

		// get ascii value
		char ascii = pEvent->text().at( 0 ).toAscii();

		if( ascii == 0 ) {
			// no ascii value, don't know key
			return eq::KC_VOID;
		}

		return ascii;
	}

	void QtEventHandler::fillOriginatorID( eq::Event& eqEvent )
	{
		EQASSERT( m_pQtWindow != 0 );

		eqEvent.originator = m_pQtWindow->getWindow()->getID();
	}

	void QtEventHandler::fillRenderContext( eq::Event& eqEvent )
	{
		//FIXME: Window::getRenderContext may only be called from the pipe thread,
		//       so leave this empty for now...

		//const eq::Window* pWindow = m_pQtWindow->getWindow();
		//bool gotContext = pWindow->getRenderContext( eqEvent.pointer.x, eqEvent.pointer.y, eqEvent.context );
		////TODO warn if we didn't get a context?
	}
}
