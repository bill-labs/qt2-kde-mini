#ifndef KLOCALE_H
#define KLOCALE_H

#include <qstring.h>

// Simple i18n stubs - everything returns English text as-is
#define i18n(x) QString(x)
#define I18N_NOOP(x) x

class KLocale {
public:
    KLocale() {}
    ~KLocale() {}

    QString translate(const char *text) const { return QString(text); }
    void insertCatalogue(const QString &) {} // stub - do nothing
};

#endif // KLOCALE_H
