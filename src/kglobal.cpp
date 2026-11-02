#include "kglobal.h"
#include "klocale.h"
#include "kconfig.h"
#include "kstddirs.h"
#include "kapp.h"
#include "kcmdlineargs.h"
#include "kaboutdata.h"
#include <qdir.h>

static KLocale *s_locale = 0;
static KStandardDirs *s_dirs = 0;

KLocale *KGlobal::locale() {
    if (!s_locale) {
        s_locale = new KLocale();
    }
    return s_locale;
}

KConfig *KGlobal::config() {
    if (kapp) {
        return kapp->config();
    }
    return 0;
}

KStandardDirs *KGlobal::dirs() {
    if (!s_dirs) {
        s_dirs = new KStandardDirs();
    }
    return s_dirs;
}

QString KGlobal::dataPath(const QString &resource) {
    // Get application name from KCmdLineArgs if available
    QString appName = "qt2-kde-mini";  // default
    KAboutData *about = KCmdLineArgs::aboutData();
    if (about) {
        appName = about->appName();
    }

    // Build base path with PREFIX and appName
    QString base;
#ifdef PREFIX
    base = QString(PREFIX) + "/share/" + appName;
    // Always use PREFIX path when compiled with PREFIX
    // Don't fall back to ./ - let the application handle missing files
#else
    // Development mode - use current directory
    base = "./";
#endif

    if (resource.isEmpty()) {
        return base;
    }
    // Add separator if needed
    if (resource[0] == '/') {
        return base + resource;
    } else {
        return base + "/" + resource;
    }
}
