#ifndef KSTDDIRS_H
#define KSTDDIRS_H

#include <qstring.h>
#include <qdir.h>
#include <qstringlist.h>

// Simplified KStandardDirs - finds resources in current directory or ./data
class KStandardDirs {
public:
    KStandardDirs() {}

    // Find resource file
    QString findResource(const char *type, const QString &filename) const {
        // Try current directory first
        if (QFile::exists(filename)) {
            return filename;
        }

        // Try ./data subdirectory
        QString dataPath = QString("data/") + filename;
        if (QFile::exists(dataPath)) {
            return dataPath;
        }

        // Try ../data (for installed version)
        QString parentDataPath = QString("../data/") + filename;
        if (QFile::exists(parentDataPath)) {
            return parentDataPath;
        }

        // Try ./pics, ./sounds for specific types
        if (QString(type) == "appdata") {
            QString picsPath = QString("pics/") + filename;
            if (QFile::exists(picsPath)) {
                return picsPath;
            }

            QString soundsPath = QString("sounds/") + filename;
            if (QFile::exists(soundsPath)) {
                return soundsPath;
            }
        }

        // Return filename as-is if not found
        return filename;
    }

    // Find all resources of a type
    QStringList findAllResources(const char *type, const QString &filter) const {
        QStringList result;
        // Simple implementation - just scan current directory
        QDir dir(".");
        QStringList files = dir.entryList(filter);
        for (QStringList::Iterator it = files.begin(); it != files.end(); ++it) {
            result.append(*it);
        }
        return result;
    }

    // Find directory containing a resource
    QString findResourceDir(const char *type, const QString &filename) const {
        // Stub - just return current directory
        return QString("./");
    }
};

#endif // KSTDDIRS_H
