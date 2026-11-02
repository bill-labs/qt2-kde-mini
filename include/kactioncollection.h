#ifndef KACTIONCOLLECTION_H
#define KACTIONCOLLECTION_H

#include <qobject.h>
#include <qlist.h>
#include <qvaluelist.h>

class KAction;

// Action container
class KActionCollection : public QObject {
    Q_OBJECT

public:
    KActionCollection(QObject *parent = 0, const char *name = 0);
    virtual ~KActionCollection();

    void insert(KAction *action);
    KAction *action(const QString &name) const;
    KAction *action(int index) const;

    QValueList<KAction *> actions() const;
    QValueList<KAction *> actions(const QString &group) const;

private:
    QList<KAction> m_actions;
};

#endif // KACTIONCOLLECTION_H
