#include "kmainwindow.h"
#include "kmenubar.h"
#include "ktoolbar.h"
#include "kstatusbar.h"
#include "kactioncollection.h"
#include "kaction.h"
#include "kxmlguifactory.h"
#include <qapplication.h>
#include <stdio.h>

KMainWindow::KMainWindow(QWidget *parent, const char *name, WFlags f)
    : QMainWindow(parent, name, f),
      m_menuBar(0),
      m_statusBar(0),
      m_actionCollection(0),
      m_factory(0)
{
    // QPtrList not available in Qt2, using QList
    // Don't delete toolbars, QMainWindow handles that
}

KMainWindow::~KMainWindow() {
    delete m_actionCollection;
    delete m_factory;
}

KMenuBar *KMainWindow::menuBar() {
    if (!m_menuBar) {
        m_menuBar = new KMenuBar(this, "menubar");
        // In Qt2, menuBar is created automatically
    }
    return m_menuBar;
}

KStatusBar *KMainWindow::statusBar() {
    if (!m_statusBar) {
        m_statusBar = new KStatusBar(this, "statusbar");
        // In Qt2, statusBar is created automatically
    }
    return m_statusBar;
}

KToolBar *KMainWindow::toolBar(const char *name) {
    // Check if toolbar with this name already exists
    if (name) {
        QListIterator<KToolBar> it(m_toolBars);
        for (; it.current(); ++it) {
            if (it.current()->name() && strcmp(it.current()->name(), name) == 0) {
                return it.current();
            }
        }
    }

    // Create new toolbar
    KToolBar *tb = new KToolBar(this, name ? name : "toolbar");
    m_toolBars.append(tb);
    return tb;
}

void KMainWindow::closeEvent(QCloseEvent *e) {
    if (queryClose() && queryExit()) {
        e->accept();
        // Quit application when main window closes
        qApp->quit();
    } else {
        e->ignore();
    }
}

KActionCollection *KMainWindow::actionCollection() {
    if (!m_actionCollection) {
        m_actionCollection = new KActionCollection(this, "action collection");
    }
    return m_actionCollection;
}

KAction *KMainWindow::action(const QString &name) const {
    if (!m_actionCollection) return 0;
    return m_actionCollection->action(name);
}

void KMainWindow::createGUI() {
    // Stub - no actual XML parsing
    // In real KDE, this would load menu/toolbar layout from XML file
    // We just create empty UI structure
}

KXMLGUIFactory *KMainWindow::factory() {
    if (!m_factory) {
        m_factory = new KXMLGUIFactory(this, "gui factory");
    }
    return m_factory;
}
