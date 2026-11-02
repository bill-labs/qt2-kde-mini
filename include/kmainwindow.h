#ifndef KMAINWINDOW_H
#define KMAINWINDOW_H

#include <qmainwindow.h>
#include <qlist.h>
#include <qstring.h>

class KMenuBar;
class KToolBar;
class KStatusBar;
class KConfig;
class KActionCollection;
class KAction;
class KXMLGUIFactory;

// Simplified KMainWindow without XML UI
class KMainWindow : public QMainWindow {
    Q_OBJECT

public:
    KMainWindow(QWidget *parent = 0, const char *name = 0,
                WFlags f = WType_TopLevel | WDestructiveClose);
    virtual ~KMainWindow();

    // Menubar
    KMenuBar *menuBar();

    // Statusbar
    KStatusBar *statusBar();

    // Toolbar management
    KToolBar *toolBar(const char *name = 0);

    // Central widget (inherited from QMainWindow)
    // void setCentralWidget(QWidget *w);

    // Action management
    KActionCollection *actionCollection();
    KAction *action(const QString &name) const;

    // XML UI (stubs - no actual XML parsing)
    void createGUI();
    QString xmlFile() const { return m_xmlFile; }
    KXMLGUIFactory *factory();

    // Session management stubs
    virtual void saveProperties(KConfig *) {}
    virtual void readProperties(KConfig *) {}

    // Size management
    void setFixedSize(const QSize &size) { QMainWindow::setFixedSize(size); }
    void setFixedSize(int w, int h) { QMainWindow::setFixedSize(w, h); }

protected:
    // Query on close
    virtual bool queryClose() { return true; }
    virtual bool queryExit() { return true; }

    void closeEvent(QCloseEvent *e);

private:
    KMenuBar *m_menuBar;
    KStatusBar *m_statusBar;
    QList<KToolBar> m_toolBars;
    KActionCollection *m_actionCollection;
    KXMLGUIFactory *m_factory;
    QString m_xmlFile;
};

// Session management macro stub
#define RESTORE(type) if (false)

#endif // KMAINWINDOW_H
