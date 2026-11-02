#ifndef KCMDLINEARGS_H
#define KCMDLINEARGS_H

class KAboutData;

// Simplified command line args - just stores the about data
class KCmdLineArgs {
public:
    static void init(int argc, char **argv, KAboutData *aboutData);
    static void init(int argc, char **argv, const char *appName,
                     const char *programName, const char *version);
    static KAboutData *aboutData();
};

#endif // KCMDLINEARGS_H
