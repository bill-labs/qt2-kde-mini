#ifndef KXMLGUIFACTORY_H
#define KXMLGUIFACTORY_H

#include <qobject.h>

class QWidget;
class QPopupMenu;

// Stub for XML UI factory
class KXMLGUIFactory : public QObject {
    Q_OBJECT

public:
    KXMLGUIFactory(QObject *parent = 0, const char *name = 0)
        : QObject(parent, name) {}
    virtual ~KXMLGUIFactory() {}

    // Return container (menu/toolbar) by name
    QWidget *container(const QString &name, QObject *parent) {
        (void)name;
        (void)parent;
        // For popup menu, return null (will be created elsewhere)
        return 0;
    }
};

#endif // KXMLGUIFACTORY_H
