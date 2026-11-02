#include "kapp.h"
#include "kconfig.h"
#include <qdir.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

KApplication *KApplication::s_self = 0;

KApplication::KApplication(int &argc, char **argv)
    : QApplication(argc, argv), m_config(0)
{
    s_self = this;

    // Create config file in ~/.appname/config
    QString appName = argv[0];
    int slash = appName.findRev('/');
    if (slash >= 0) {
        appName = appName.mid(slash + 1);
    }

    QString configDir = QDir::homeDirPath() + "/." + appName;
    QDir dir;
    if (!dir.exists(configDir)) {
        dir.mkdir(configDir);
    }

    QString configFile = configDir + "/config";
    m_config = new KConfig(configFile);
}

KApplication::~KApplication() {
    delete m_config;
    s_self = 0;
}

KApplication *KApplication::kApplication() {
    return s_self;
}

KConfig *KApplication::config() {
    return m_config;
}

void KApplication::setMainWidget(QWidget *widget) {
    QApplication::setMainWidget(widget);
}

void KApplication::setTopWidget(QWidget *widget) {
    // In Qt2, this is the same as setMainWidget
    setMainWidget(widget);
}

// Random number generator - matches KDE2 kdecore/kapp.cpp implementation
int KApplication::random()
{
   static int init = false;
   if (!init)
   {
      unsigned int seed;
      init = true;
      int fd = open("/dev/urandom", O_RDONLY);
      if (fd <= 0 || ::read(fd, &seed, sizeof(seed)) != sizeof(seed))
      {
            // No /dev/urandom... try something else.
            srand(getpid());
            seed = rand()+time(0);
      }
      if (fd >= 0) close(fd);
      srand(seed);
   }
   return rand();
}
