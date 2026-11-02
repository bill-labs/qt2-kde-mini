#include "kconfig.h"
#include <qfile.h>
#include <qtextstream.h>

KConfig::KConfig(const QString &fileName)
    : m_fileName(fileName), m_currentGroup("General"), m_dirty(false)
{
    if (!m_fileName.isEmpty()) {
        load();
    }
}

KConfig::~KConfig() {
    if (m_dirty) {
        sync();
    }
}

void KConfig::setGroup(const QString &group) {
    m_currentGroup = group.isEmpty() ? QString("General") : group;
}

QString KConfig::makeKey(const QString &key) const {
    return m_currentGroup + "/" + key;
}

QString KConfig::readEntry(const QString &key, const QString &defaultValue) const {
    QString fullKey = makeKey(key);
    if (m_data.contains(fullKey)) {
        return m_data[fullKey];
    }
    return defaultValue;
}

int KConfig::readNumEntry(const QString &key, int defaultValue) const {
    QString value = readEntry(key);
    if (value.isEmpty()) {
        return defaultValue;
    }
    bool ok;
    int result = value.toInt(&ok);
    return ok ? result : defaultValue;
}

unsigned int KConfig::readUnsignedNumEntry(const QString &key, unsigned int defaultValue) const {
    QString value = readEntry(key);
    if (value.isEmpty()) {
        return defaultValue;
    }
    bool ok;
    unsigned int result = value.toUInt(&ok);
    return ok ? result : defaultValue;
}

bool KConfig::readBoolEntry(const QString &key, bool defaultValue) const {
    QString value = readEntry(key).lower();
    if (value.isEmpty()) {
        return defaultValue;
    }
    return (value == "true" || value == "1" || value == "yes");
}

void KConfig::writeEntry(const QString &key, const QString &value) {
    QString fullKey = makeKey(key);
    m_data[fullKey] = value;
    m_dirty = true;
}

void KConfig::writeEntry(const QString &key, int value) {
    writeEntry(key, QString::number(value));
}

void KConfig::writeEntry(const QString &key, unsigned int value) {
    writeEntry(key, QString::number(value));
}

void KConfig::writeEntry(const QString &key, bool value) {
    writeEntry(key, value ? QString("true") : QString("false"));
}

bool KConfig::hasKey(const QString &key) const {
    return m_data.contains(makeKey(key));
}

void KConfig::load() {
    if (m_fileName.isEmpty()) return;

    QFile file(m_fileName);
    if (!file.open(IO_ReadOnly)) return;

    QTextStream stream(&file);
    QString currentGroup = "General";

    while (!stream.atEnd()) {
        QString line = stream.readLine().stripWhiteSpace();

        // Skip empty lines and comments
        if (line.isEmpty() || line[0] == '#') continue;

        // Group header
        if (line[0] == '[' && line[line.length()-1] == ']') {
            currentGroup = line.mid(1, line.length()-2);
            continue;
        }

        // Key=Value pair
        int eq = line.find('=');
        if (eq > 0) {
            QString key = line.left(eq).stripWhiteSpace();
            QString value = line.mid(eq+1).stripWhiteSpace();
            m_data[currentGroup + "/" + key] = value;
        }
    }

    file.close();
    m_dirty = false;
}

void KConfig::save() {
    if (m_fileName.isEmpty()) return;

    QFile file(m_fileName);
    if (!file.open(IO_WriteOnly)) return;

    QTextStream stream(&file);

    // Collect all groups
    QMap<QString, QMap<QString, QString> > groups;
    QMap<QString, QString>::Iterator it;
    for (it = m_data.begin(); it != m_data.end(); ++it) {
        QString fullKey = it.key();
        int slash = fullKey.find('/');
        if (slash > 0) {
            QString group = fullKey.left(slash);
            QString key = fullKey.mid(slash+1);
            groups[group][key] = it.data();
        }
    }

    // Write groups
    QMap<QString, QMap<QString, QString> >::Iterator git;
    for (git = groups.begin(); git != groups.end(); ++git) {
        stream << "[" << git.key() << "]\n";
        QMap<QString, QString>::Iterator kit;
        for (kit = git.data().begin(); kit != git.data().end(); ++kit) {
            stream << kit.key() << "=" << kit.data() << "\n";
        }
        stream << "\n";
    }

    file.close();
}

void KConfig::sync() {
    if (m_dirty) {
        save();
        m_dirty = false;
    }
}

QColor KConfig::readColorEntry(const QString &key, const QColor &defaultValue) const {
    QString value = readEntry(key);
    if (value.isEmpty()) return defaultValue;
    // Parse color from string (format: "r,g,b")
    int r = 0, g = 0, b = 0;
    sscanf(value.latin1(), "%d,%d,%d", &r, &g, &b);
    return QColor(r, g, b);
}

void KConfig::writeEntry(const QString &key, const QColor &value) {
    QString str;
    str.sprintf("%d,%d,%d", value.red(), value.green(), value.blue());
    writeEntry(key, str);
}

QStringList KConfig::readListEntry(const QString &key, char sep) const {
    QString value = readEntry(key);
    if (value.isEmpty()) {
        return QStringList();
    }
    
    // Split by separator
    QStringList result;
    QString current;
    for (unsigned int i = 0; i < value.length(); i++) {
        if (value[i] == sep) {
            if (!current.isEmpty()) {
                result.append(current);
                current = QString::null;
            }
        } else {
            current += value[i];
        }
    }
    if (!current.isEmpty()) {
        result.append(current);
    }
    return result;
}
