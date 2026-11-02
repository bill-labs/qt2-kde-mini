#include "kaccel.h"
#include <qwidget.h>
#include <qnamespace.h>

KAccel::KAccel(QWidget *parent, const char *name)
    : QObject(parent, name)
{
    m_accel = new QAccel(parent);
}

KAccel::~KAccel()
{
    delete m_accel;
}

bool KAccel::insert(const QString &action, const QString &label,
                    const QString &whatsThis, int key,
                    const QObject *receiver, const char *slot)
{
    (void)action;
    (void)label;
    (void)whatsThis;

    if (key == 0 || !receiver || !slot) return false;

    int id = m_accel->insertItem(key);
    m_accel->connectItem(id, receiver, slot);
    return true;
}

bool KAccel::setEnabled(const QString &action, bool enabled)
{
    (void)action;
    (void)enabled;
    return true;
}

int KAccel::stringToKey(const QString &keyStr)
{
    // Simplified parser for accelerator strings like "CTRL+R", "ALT+F4", etc.
    if (keyStr.isEmpty()) return 0;

    int result = 0;
    QString upper = keyStr.upper();

    // Parse modifiers
    if (upper.contains("CTRL") || upper.contains("CONTROL"))
        result |= Qt::CTRL;
    if (upper.contains("ALT"))
        result |= Qt::ALT;
    if (upper.contains("SHIFT"))
        result |= Qt::SHIFT;

    // Find the key part (after last '+')
    int plusPos = upper.findRev('+');
    QString keyPart = (plusPos >= 0) ? upper.mid(plusPos + 1).stripWhiteSpace() : upper;

    // Simple key mapping - just handle common cases
    if (keyPart.length() == 1) {
        result |= keyPart[0].latin1();
    } else if (keyPart == "F1") result |= Qt::Key_F1;
    else if (keyPart == "F2") result |= Qt::Key_F2;
    else if (keyPart == "F3") result |= Qt::Key_F3;
    else if (keyPart == "F4") result |= Qt::Key_F4;
    else if (keyPart == "F5") result |= Qt::Key_F5;
    else if (keyPart == "RETURN" || keyPart == "ENTER") result |= Qt::Key_Return;
    else if (keyPart == "ESC" || keyPart == "ESCAPE") result |= Qt::Key_Escape;
    else if (keyPart == "TAB") result |= Qt::Key_Tab;

    return result;
}
