#ifndef KICONLOADER_H
#define KICONLOADER_H

#include <qpixmap.h>
#include <qstring.h>
#include "kicon.h"

// Simplified KIconLoader - loads icons from current directory
class KIconLoader {
public:
    KIconLoader() {}

    // Load icon by name
    QPixmap loadIcon(const QString &name, int size = 16) const {
        // Try to load from current directory
        QPixmap pix(name);
        if (!pix.isNull()) {
            return pix;
        }

        // Try with .png extension
        pix.load(name + ".png");
        if (!pix.isNull()) {
            return pix;
        }

        // Try in pics/ subdirectory
        pix.load(QString("pics/") + name);
        if (!pix.isNull()) {
            return pix;
        }

        pix.load(QString("pics/") + name + ".png");
        if (!pix.isNull()) {
            return pix;
        }

        // Return null pixmap if not found
        return QPixmap();
    }

    // Load application icon
    QPixmap loadApplicationIcon(const QString &name, int size = 32) const {
        return loadIcon(name, size);
    }
};

// Global functions for icon loading
inline QPixmap SmallIcon(const QString &name) {
    static KIconLoader loader;
    return loader.loadIcon(name, 16); // KIcon::Small
}

inline QPixmap BarIcon(const QString &name, int size = KIcon::SizeSmall) {
    static KIconLoader loader;
    return loader.loadIcon(name, size);
}

inline QPixmap DesktopIcon(const QString &name) {
    static KIconLoader loader;
    return loader.loadIcon(name, 32); // KIcon::Medium
}

#endif // KICONLOADER_H
