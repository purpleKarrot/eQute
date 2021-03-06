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

#ifndef EQQT_QTMAINWINDOW_H
#define EQQT_QTMAINWINDOW_H

#include <eq/client/event.h>

#include <QtCore/QMutex>
#include <QtGui/QMainWindow>

#include "qtEventHandler.h"
#include "qtWindowListener.h"

class QKeyEvent;
class QCloseEvent;

namespace eqQt
{

class EqShutdownEvent;
class QtWindow;

// Implementation of a QMainWindow that forwards events it receives
// to a QtEventHandler (if one is set).
// Meant to be subclassed by an application-specific MainWindow.
class QtMainWindow: public QMainWindow, protected QtWindowListener
{
public:
	QtMainWindow(QtWindow* window, QWidget* pParent = 0);
	virtual ~QtMainWindow();

protected:
	eqQt::QtWindow* lockQtWindow();
	void unlockQtWindow();

	virtual bool event(QEvent* pEvent);

	virtual void keyPressEvent(QKeyEvent* pEvent);
	virtual void keyReleaseEvent(QKeyEvent* pEvent);

	virtual void closeEvent(QCloseEvent* pEvent);

	virtual void eqShutdownEvent(EqShutdownEvent* pEvent);

	virtual void beforeConfigExit();
	virtual void afterConfigExit();

private:
	QtWindow* m_pQtWindow;
	QMutex m_mutex;

	QtEventHandler m_qtEventHandler;
};

} // namespace eqQt

#endif // EQQT_QTMAINWINDOW_H
