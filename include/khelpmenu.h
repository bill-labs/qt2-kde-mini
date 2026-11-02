#ifndef KHELPMENU_H
#define KHELPMENU_H

#include <qpopupmenu.h>
#include <qmessagebox.h>
#include "kaboutdata.h"

// Simplified KHelpMenu - creates a simple help menu
class KHelpMenu : public QObject {
    Q_OBJECT

public:
    KHelpMenu(QWidget *parent = 0, const KAboutData *aboutData = 0, bool showWhatsThis = true)
        : QObject(parent), m_parent(parent), m_aboutData(aboutData)
    {
        m_menu = new QPopupMenu(parent);
        m_menu->insertItem("&About", this, SLOT(aboutApplication()));
    }

    ~KHelpMenu() {
        delete m_menu;
    }

    QPopupMenu *menu() { return m_menu; }

private slots:
    void aboutApplication() {
        QString aboutText = "Application";
        if (m_aboutData) {
            aboutText = QString("%1 %2\n%3")
                .arg(m_aboutData->programName())
                .arg(m_aboutData->version())
                .arg(m_aboutData->shortDescription());

            QString copyright = m_aboutData->copyrightStatement();
            if (!copyright.isEmpty()) {
                aboutText += QString("\n\n%1").arg(copyright);
            }
        }
        QMessageBox::about(m_parent, "About", aboutText);
    }

private:
    QWidget *m_parent;
    const KAboutData *m_aboutData;
    QPopupMenu *m_menu;
};

#endif // KHELPMENU_H
