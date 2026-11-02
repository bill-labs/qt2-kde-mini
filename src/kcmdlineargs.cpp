#include "kcmdlineargs.h"
#include "kaboutdata.h"

static KAboutData *s_aboutData = 0;

void KCmdLineArgs::init(int argc, char **argv, KAboutData *aboutData) {
    s_aboutData = aboutData;
}

void KCmdLineArgs::init(int argc, char **argv, const char *appName,
                        const char *programName, const char *version) {
    s_aboutData = new KAboutData(appName, programName, version);
}

KAboutData *KCmdLineArgs::aboutData() {
    return s_aboutData;
}
