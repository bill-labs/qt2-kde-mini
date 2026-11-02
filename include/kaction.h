#ifndef KACTION_H
#define KACTION_H

#include <qobject.h>
#include <qstring.h>
#include <qlist.h>
#include <qiconset.h>

class QPopupMenu;
class KToolBar;
class QWidget;
class KAccel;
class KActionCollection;

// Simplified KAction without XML UI
// Manages menu items, toolbar buttons, and keyboard shortcuts
class KAction : public QObject {
    Q_OBJECT

public:
    KAction(const QString &text, int accel,
            const QObject *receiver, const char *slot,
            QObject *parent, const char *name = 0);

    KAction(const QString &text, const QIconSet &icon, int accel,
            const QObject *receiver, const char *slot,
            QObject *parent, const char *name = 0);

    KAction(const QString &text, const QString &icon, int accel,
            const QObject *receiver, const char *slot,
            QObject *parent, const char *name = 0);

    // Constructor with KActionCollection (for XML UI style)
    KAction(const QString &text, int accel,
            const QObject *receiver, const char *slot,
            KActionCollection *parent, const char *name);

    // Constructor with icon and KActionCollection
    KAction(const QString &text, const QString &icon, int accel,
            const QObject *receiver, const char *slot,
            KActionCollection *parent, const char *name);

    virtual ~KAction();

    // Plug into menu or toolbar
    virtual int plug(QWidget *widget, int index = -1);
    virtual void unplug(QWidget *widget);

    // Plug into accelerator
    virtual void plugAccel(KAccel *accel);

    // Enable/disable
    virtual void setEnabled(bool enable);
    bool isEnabled() const { return m_enabled; }

    // Text and icon
    virtual void setText(const QString &text);
    QString text() const { return m_text; }

    virtual void setIcon(const QString &icon);
    virtual void setIconSet(const QIconSet &iconSet);

    // Tooltip and status tip
    virtual void setToolTip(const QString &tip);
    virtual void setStatusTip(const QString &tip);

    // Shortcut
    virtual void setAccel(int key);
    int accel() const { return m_accel; }

    // Name and group
    QString name() const { return m_name; }
    QString group() const { return m_group; }
    void setGroup(const QString &group) { m_group = group; }

public slots:
    void activate();

signals:
    void activated();

protected:
    void init(const QString &text, int accel,
              const QObject *receiver, const char *slot);

    QString m_name;
    QString m_group;
    QString m_text;
    QIconSet m_iconSet;
    int m_accel;
    bool m_enabled;
    QString m_toolTip;
    QString m_statusTip;

    struct PlugInfo {
        QWidget *widget;
        int id;
    };
    QList<PlugInfo> m_plugged;
};

// KToggleAction - action with on/off state
class KToggleAction : public KAction {
    Q_OBJECT

public:
    KToggleAction(const QString &text, int accel,
                  const QObject *receiver, const char *slot,
                  QObject *parent, const char *name = 0);

    KToggleAction(const QString &text, const QString &icon, int accel,
                  const QObject *receiver, const char *slot,
                  KActionCollection *parent, const char *name = 0);

    KToggleAction(const QString &text, int accel,
                  const QObject *receiver, const char *slot,
                  KActionCollection *parent, const char *name = 0);

    virtual ~KToggleAction();

    virtual int plug(QWidget *widget, int index = -1);

    void setChecked(bool checked);
    bool isChecked() const { return m_checked; }

protected slots:
    void slotToggled(bool checked);
    void slotActivated();  // For menu activation

signals:
    void toggled(bool checked);

private:
    bool m_checked;
};

// KRadioAction - mutually exclusive toggle action
class KRadioAction : public KToggleAction {
    Q_OBJECT

public:
    KRadioAction(const QString &text, int accel,
                 const QObject *receiver, const char *slot,
                 QObject *parent, const char *name = 0);

    KRadioAction(const QString &text, int accel,
                 const QObject *receiver, const char *slot,
                 KActionCollection *parent, const char *name);

    virtual ~KRadioAction();

    void setExclusiveGroup(const QString &group);
    QString exclusiveGroup() const { return m_exclusiveGroup; }

private:
    QString m_exclusiveGroup;
};

// KSelectAction - action with list of choices
class KSelectAction : public KAction {
    Q_OBJECT

public:
    KSelectAction(const QString &text, int accel,
                  const QObject *receiver, const char *slot,
                  QObject *parent, const char *name = 0);

    KSelectAction(const QString &text, int accel,
                  const QObject *receiver, const char *slot,
                  KActionCollection *parent, const char *name);

    virtual ~KSelectAction();

    virtual int plug(QWidget *widget, int index = -1);

    void setItems(const QStringList &items);
    QStringList items() const { return m_items; }

    void setCurrentItem(int index);
    int currentItem() const { return m_currentItem; }

protected slots:
    void slotActivated(int id);

signals:
    void activated(int index);

private:
    QStringList m_items;
    int m_currentItem;
    QPopupMenu *m_popup;
};

#endif // KACTION_H
