#ifndef KKEYDIALOG_H
#define KKEYDIALOG_H

#include <qstring.h>

class KAccel;
class KGlobalAccel;
class KActionCollection;
class QWidget;

// Stub - key binding configuration dialog
class KKeyDialog {
public:
    // Configure key bindings (stub - does nothing)
    static void configureKeys(KAccel *) {}
    static void configureKeys(KGlobalAccel *) {}
    static void configure(KActionCollection *, bool = false) {}
    static void configureKeys(KActionCollection *, const QString &,
                             bool = false, QWidget * = 0) {}
};

#endif // KKEYDIALOG_H
