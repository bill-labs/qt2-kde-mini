#ifndef KGLOBAL_H
#define KGLOBAL_H

#include <qstring.h>

class KLocale;
class KConfig;
class KStandardDirs;

class KGlobal {
public:
    static KLocale *locale();
    static KConfig *config();
    static KStandardDirs *dirs();
    static QString dataPath(const QString &resource);
};

#endif // KGLOBAL_H
