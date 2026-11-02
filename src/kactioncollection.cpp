#include "kactioncollection.h"
#include "kaction.h"

KActionCollection::KActionCollection(QObject *parent, const char *name)
    : QObject(parent, name)
{
    m_actions.setAutoDelete(false);
}

KActionCollection::~KActionCollection()
{
}

void KActionCollection::insert(KAction *action)
{
    if (action) {
        m_actions.append(action);
    }
}

KAction *KActionCollection::action(const QString &name) const
{
    QListIterator<KAction> it(m_actions);
    for (; it.current(); ++it) {
        if (it.current()->name() == name) {
            return it.current();
        }
    }
    return 0;
}

KAction *KActionCollection::action(int index) const
{
    // QList::at() is not const, so we need to cast
    return ((QList<KAction>&)m_actions).at(index);
}

QValueList<KAction *> KActionCollection::actions() const
{
    QValueList<KAction *> result;
    QListIterator<KAction> it(m_actions);
    for (; it.current(); ++it) {
        result.append(it.current());
    }
    return result;
}

QValueList<KAction *> KActionCollection::actions(const QString &group) const
{
    QValueList<KAction *> result;
    QListIterator<KAction> it(m_actions);
    for (; it.current(); ++it) {
        if (it.current()->group() == group) {
            result.append(it.current());
        }
    }
    return result;
}
