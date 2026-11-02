#ifndef KHIGHSCORE_H
#define KHIGHSCORE_H

#include <qstring.h>
#include <qstringlist.h>

// Stub - highscore management
class KHighscore {
public:
    KHighscore() {}

    // Check if table exists
    bool hasTable() const { return false; }

    void setHighscoreGroup(const QString &) {}
    QString readEntry(uint, const QString &, const QString & = QString::null) { return QString::null; }
    void writeEntry(uint, const QString &, const QString &) {}

    QStringList readList(const QString &, int) { return QStringList(); }
    void writeList(const QString &, const QStringList &) {}

    // Sync data (no-op in stub)
    void sync() {}
};

#endif // KHIGHSCORE_H
