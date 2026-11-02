#include "kaction.h"
#include "kactioncollection.h"
#include "ktoolbar.h"
#include <stdio.h>
#include <qpopupmenu.h>
#include <qtoolbutton.h>
#include <qaccel.h>
#include <qtooltip.h>
#include <qpixmap.h>
#include <qstringlist.h>

// KAction implementation

KAction::KAction(const QString &text, int accel,
                 const QObject *receiver, const char *slot,
                 QObject *parent, const char *name)
    : QObject(parent, name), m_enabled(true)
{
    if (name) m_name = QString(name);
    init(text, accel, receiver, slot);
}

KAction::KAction(const QString &text, const QIconSet &icon, int accel,
                 const QObject *receiver, const char *slot,
                 QObject *parent, const char *name)
    : QObject(parent, name), m_iconSet(icon), m_enabled(true)
{
    if (name) m_name = QString(name);
    init(text, accel, receiver, slot);
}

KAction::KAction(const QString &text, const QString &icon, int accel,
                 const QObject *receiver, const char *slot,
                 QObject *parent, const char *name)
    : QObject(parent, name), m_enabled(true)
{
    if (name) m_name = QString(name);
    if (!icon.isEmpty()) {
        QPixmap pix(icon);
        if (!pix.isNull()) {
            m_iconSet = QIconSet(pix);
        }
    }
    init(text, accel, receiver, slot);
}

KAction::KAction(const QString &text, int accel,
                 const QObject *receiver, const char *slot,
                 KActionCollection *parent, const char *name)
    : QObject((QObject*)parent, name), m_enabled(true)
{
    if (name) m_name = QString(name);
    init(text, accel, receiver, slot);
    if (parent) {
        parent->insert(this);
    }
}

KAction::KAction(const QString &text, const QString &icon, int accel,
                 const QObject *receiver, const char *slot,
                 KActionCollection *parent, const char *name)
    : QObject((QObject*)parent, name), m_enabled(true)
{
    if (name) m_name = QString(name);
    if (!icon.isEmpty()) {
        QPixmap pix(icon);
        if (!pix.isNull()) {
            m_iconSet = QIconSet(pix);
        }
    }
    init(text, accel, receiver, slot);
    if (parent) {
        parent->insert(this);
    }
}

KAction::~KAction() {
    m_plugged.setAutoDelete(true);
}

void KAction::init(const QString &text, int accel,
                  const QObject *receiver, const char *slot)
{
    m_text = text;
    m_accel = accel;

    if (receiver && slot) {
        connect(this, SIGNAL(activated()), receiver, slot);
    }

    m_plugged.setAutoDelete(true);
}

int KAction::plug(QWidget *widget, int index) {
    if (!widget) return -1;

    int id = -1;

    if (widget->inherits("QPopupMenu")) {
        QPopupMenu *menu = (QPopupMenu*)widget;
        bool hasValidIcon = !m_iconSet.isNull() && !m_iconSet.pixmap().isNull();
        if (!hasValidIcon) {
            id = menu->insertItem(m_text, this, SLOT(activate()), m_accel, -1, index);
        } else {
            id = menu->insertItem(m_iconSet, m_text, this, SLOT(activate()), m_accel, -1, index);
        }
        menu->setItemEnabled(id, m_enabled);

        PlugInfo *info = new PlugInfo;
        info->widget = widget;
        info->id = id;
        m_plugged.append(info);

    } else if (widget->inherits("KToolBar")) {
        KToolBar *toolBar = (KToolBar*)widget;
        QToolButton *btn;
        bool hasValidIcon = !m_iconSet.isNull() && !m_iconSet.pixmap().isNull();

        btn = new QToolButton(toolBar);
        if (hasValidIcon) {
            btn->setIconSet(m_iconSet);
        }
        btn->setTextLabel(m_text);
        btn->setUsesTextLabel(!hasValidIcon); // Show text only if no icon

        btn->setEnabled(m_enabled);
        if (!m_toolTip.isEmpty()) {
            QToolTip::add(btn, m_toolTip);
        }

        connect(btn, SIGNAL(clicked()), this, SLOT(activate()));

        PlugInfo *info = new PlugInfo;
        info->widget = widget;
        info->id = -1; // toolbar doesn't use ids
        m_plugged.append(info);

        id = 0;
    }

    return id;
}

void KAction::unplug(QWidget *widget) {
    QListIterator<PlugInfo> it(m_plugged);
    for (; it.current(); ++it) {
        PlugInfo *info = it.current();
        if (info && info->widget == widget) {
            m_plugged.remove(info);
            break;
        }
    }
}

void KAction::setEnabled(bool enable) {
    m_enabled = enable;

    // Update all plugged widgets
    QListIterator<PlugInfo> it(m_plugged);
    for (; it.current(); ++it) {
        PlugInfo *info = it.current();
        if (!info || !info->widget) continue;

        QWidget *w = info->widget;
        if (w->inherits("QPopupMenu")) {
            ((QPopupMenu*)w)->setItemEnabled(info->id, enable);
        } else if (w->inherits("KToolBar")) {
            // Find the button in toolbar and enable/disable it
            // This is simplified - in real KDE there's better tracking
        }
    }
}

void KAction::setText(const QString &text) {
    m_text = text;
    // TODO: update plugged widgets
}

void KAction::setIcon(const QString &icon) {
    QPixmap pix(icon);
    if (!pix.isNull()) {
        setIconSet(QIconSet(pix));
    }
}

void KAction::setIconSet(const QIconSet &iconSet) {
    m_iconSet = iconSet;
    // TODO: update plugged widgets
}

void KAction::setToolTip(const QString &tip) {
    m_toolTip = tip;
}

void KAction::setStatusTip(const QString &tip) {
    m_statusTip = tip;
}

void KAction::setAccel(int key) {
    m_accel = key;
}

void KAction::activate() {
    if (m_enabled) {
        emit activated();
    }
}

void KAction::plugAccel(KAccel *accel) {
    // Accelerator will be handled by KAccel class
    // This is a simplified implementation
    (void)accel;
}

// KToggleAction implementation

KToggleAction::KToggleAction(const QString &text, int accel,
                             const QObject *receiver, const char *slot,
                             QObject *parent, const char *name)
    : KAction(text, accel, 0, 0, parent, name), m_checked(false)
{
    if (receiver && slot) {
        connect(this, SIGNAL(toggled(bool)), receiver, slot);
    }
}

KToggleAction::KToggleAction(const QString &text, int accel,
                             const QObject *receiver, const char *slot,
                             KActionCollection *parent, const char *name)
    : KAction(text, accel, 0, 0, (QObject*)parent, name), m_checked(false)
{
    if (name) m_name = QString(name);
    if (receiver && slot) {
        connect(this, SIGNAL(toggled(bool)), receiver, slot);
    }
    if (parent) {
        parent->insert(this);
    }
}

KToggleAction::KToggleAction(const QString &text, const QString &icon, int accel,
                             const QObject *receiver, const char *slot,
                             KActionCollection *parent, const char *name)
    : KAction(text, icon, accel, 0, 0, (QObject*)parent, name), m_checked(false)
{
    if (name) m_name = QString(name);
    if (receiver && slot) {
        connect(this, SIGNAL(toggled(bool)), receiver, slot);
    }
    if (parent) {
        parent->insert(this);
    }
}

KToggleAction::~KToggleAction() {
}

int KToggleAction::plug(QWidget *widget, int index) {
    if (!widget) return -1;

    int id = -1;

    if (widget->inherits("QPopupMenu")) {
        QPopupMenu *menu = (QPopupMenu*)widget;
        id = menu->insertItem(m_text, this, SLOT(slotActivated()), m_accel, -1, index);
        menu->setItemChecked(id, m_checked);
        menu->setItemEnabled(id, m_enabled);

        PlugInfo *info = new PlugInfo;
        info->widget = widget;
        info->id = id;
        m_plugged.append(info);
    }

    return id;
}

void KToggleAction::setChecked(bool checked) {
    if (m_checked == checked) return;

    m_checked = checked;

    // Update all plugged widgets
    QListIterator<PlugInfo> it(m_plugged);
    for (; it.current(); ++it) {
        PlugInfo *info = it.current();
        if (!info || !info->widget) continue;

        QWidget *w = info->widget;
        if (w->inherits("QPopupMenu")) {
            ((QPopupMenu*)w)->setItemChecked(info->id, checked);
        }
    }

    emit toggled(checked);
}

void KToggleAction::slotToggled(bool checked) {
    setChecked(checked);
}

void KToggleAction::slotActivated() {
    setChecked(!m_checked);  // Toggle state
}

// KRadioAction implementation

KRadioAction::KRadioAction(const QString &text, int accel,
                           const QObject *receiver, const char *slot,
                           QObject *parent, const char *name)
    : KToggleAction(text, accel, receiver, slot, parent, name)
{
}

KRadioAction::~KRadioAction() {
}

KRadioAction::KRadioAction(const QString &text, int accel,
                           const QObject *receiver, const char *slot,
                           KActionCollection *parent, const char *name)
    : KToggleAction(text, accel, receiver, slot, (QObject*)parent, name)
{
    if (parent) {
        parent->insert(this);
    }
}

void KRadioAction::setExclusiveGroup(const QString &group) {
    m_exclusiveGroup = group;
}

// KSelectAction implementation

KSelectAction::KSelectAction(const QString &text, int accel,
                             const QObject *receiver, const char *slot,
                             QObject *parent, const char *name)
    : KAction(text, accel, 0, 0, parent, name), m_currentItem(-1), m_popup(0)
{
    if (receiver && slot) {
        connect(this, SIGNAL(activated(int)), receiver, slot);
    }
}

KSelectAction::KSelectAction(const QString &text, int accel,
                             const QObject *receiver, const char *slot,
                             KActionCollection *parent, const char *name)
    : KAction(text, accel, 0, 0, (QObject*)parent, name), m_currentItem(-1), m_popup(0)
{
    if (receiver && slot) {
        connect(this, SIGNAL(activated(int)), receiver, slot);
    }
    if (parent) {
        parent->insert(this);
    }
}

KSelectAction::~KSelectAction() {
    delete m_popup;
}

int KSelectAction::plug(QWidget *widget, int index) {
    if (!widget) return -1;

    if (widget->inherits("QPopupMenu")) {
        QPopupMenu *menu = (QPopupMenu*)widget;

        // Create submenu if not exists
        if (!m_popup) {
            m_popup = new QPopupMenu(widget);
            connect(m_popup, SIGNAL(activated(int)), this, SLOT(slotActivated(int)));
        }

        // Add items to submenu
        m_popup->clear();
        for (int i = 0; i < (int)m_items.count(); i++) {
            m_popup->insertItem(m_items[i], i);
            if (i == m_currentItem) {
                m_popup->setItemChecked(i, true);
            }
        }

        // Insert submenu into parent menu
        int id = menu->insertItem(m_text, m_popup, -1, index);
        menu->setItemEnabled(id, m_enabled);

        PlugInfo *info = new PlugInfo;
        info->widget = widget;
        info->id = id;
        m_plugged.append(info);

        return id;
    }

    return -1;
}

void KSelectAction::slotActivated(int id) {
    setCurrentItem(id);
    emit activated(id);
}

void KSelectAction::setItems(const QStringList &items) {
    m_items = items;
}

void KSelectAction::setCurrentItem(int index) {
    if (m_currentItem == index) return;

    // Uncheck old item
    if (m_popup && m_currentItem >= 0 && m_currentItem < (int)m_items.count()) {
        m_popup->setItemChecked(m_currentItem, false);
    }

    m_currentItem = index;

    // Check new item
    if (m_popup && m_currentItem >= 0 && m_currentItem < (int)m_items.count()) {
        m_popup->setItemChecked(m_currentItem, true);
    }
}
