#ifndef KACCEL_H
#define KACCEL_H

#include <qobject.h>
#include <qaccel.h>
#include <qstring.h>

class KAction;

// Simplified keyboard accelerator management
class KAccel : public QObject {
    Q_OBJECT

public:
    KAccel(QWidget *parent, const char *name = 0);
    virtual ~KAccel();

    bool insert(const QString &action, const QString &label,
                const QString &whatsThis, int key,
                const QObject *receiver, const char *slot);

    bool setEnabled(const QString &action, bool enabled);

    // Convert string like "CTRL+R" to key code
    static int stringToKey(const QString &keyStr);

private:
    QAccel *m_accel;
};

// Global accelerator (stub)
class KGlobalAccel : public QObject {
    Q_OBJECT

public:
    KGlobalAccel(QObject *parent, const char *name = 0) : QObject(parent, name) {}
    virtual ~KGlobalAccel() {}

    bool insert(const QString &, const QString &, const QString &,
                int, const QObject *, const char *) { return true; }
};

#endif // KACCEL_H
