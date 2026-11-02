#ifndef KCONFIG_H
#define KCONFIG_H

#include <qstring.h>
#include <qmap.h>
#include <qcolor.h>
#include <qstringlist.h>

// Simplified KConfig - stores config in memory and saves to file
class KConfig {
public:
    KConfig(const QString &fileName = QString::null);
    ~KConfig();

    // Group management
    void setGroup(const QString &group);
    QString group() const { return m_currentGroup; }

    // Read entries
    QString readEntry(const QString &key, const QString &defaultValue = QString::null) const;
    int readNumEntry(const QString &key, int defaultValue = 0) const;
    unsigned int readUnsignedNumEntry(const QString &key, unsigned int defaultValue = 0) const;
    bool readBoolEntry(const QString &key, bool defaultValue = false) const;
    QColor readColorEntry(const QString &key, const QColor &defaultValue = QColor()) const;
    QStringList readListEntry(const QString &key, char sep = ',') const;

    // Write entries
    void writeEntry(const QString &key, const QString &value);
    void writeEntry(const QString &key, int value);
    void writeEntry(const QString &key, unsigned int value);
    void writeEntry(const QString &key, bool value);
    void writeEntry(const QString &key, const QColor &value);

    // Check if entry exists
    bool hasKey(const QString &key) const;

    // Sync to disk
    void sync();

private:
    QString makeKey(const QString &key) const;
    void load();
    void save();

    QString m_fileName;
    QString m_currentGroup;
    QMap<QString, QString> m_data;
    bool m_dirty;
};

#endif // KCONFIG_H
