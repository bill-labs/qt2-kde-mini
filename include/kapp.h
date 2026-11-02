#ifndef KAPP_H
#define KAPP_H

#include <qapplication.h>

class KConfig;

// KApplication - simplified wrapper around QApplication
class KApplication : public QApplication {
    Q_OBJECT

public:
    KApplication(int &argc, char **argv);
    virtual ~KApplication();

    static KApplication *kApplication();

    // Config access
    KConfig *config();

    // Session management stubs
    bool isRestored() const { return false; }
    void setMainWidget(QWidget *widget);
    void setTopWidget(QWidget *widget);

    // Help invocation (stub - does nothing)
    void invokeHelp(const QString &anchor = QString::null, const QString &appname = QString::null) {}

    // Random number generator (for KRandomSequence)
    static int random();

private:
    KConfig *m_config;
    static KApplication *s_self;
};

// Convenience macro
#define kapp KApplication::kApplication()

#endif // KAPP_H
