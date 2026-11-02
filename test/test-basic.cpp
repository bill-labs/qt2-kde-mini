// Simple test for qt2-kde-mini library
// Tests: KApplication, KConfig, i18n, KAboutData

#include <qapplication.h>
#include <qmainwindow.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qvbox.h>
#include <qmessagebox.h>

#include "kapp.h"
#include "kconfig.h"
#include "klocale.h"
#include "kaboutdata.h"
#include "kcmdlineargs.h"
#include "kglobal.h"

class TestWindow : public QMainWindow {
    Q_OBJECT

public:
    TestWindow() : QMainWindow(0, "TestWindow") {
        setCaption(i18n("qt2-kde-mini Test"));

        QVBox *vbox = new QVBox(this);
        setCentralWidget(vbox);

        // Test i18n
        QLabel *label1 = new QLabel(i18n("Testing qt2-kde-mini library"), vbox);
        label1->setAlignment(Qt::AlignCenter);

        // Test KConfig - read counter
        KConfig *config = KGlobal::config();
        config->setGroup("Test");
        int counter = config->readNumEntry("LaunchCount", 0);
        counter++;

        QString text;
        text.sprintf("Application launched %d times", counter);
        QLabel *label2 = new QLabel(text, vbox);
        label2->setAlignment(Qt::AlignCenter);

        // Save new counter value
        config->writeEntry("LaunchCount", counter);
        config->sync();

        // Buttons
        QPushButton *aboutBtn = new QPushButton(i18n("About"), vbox);
        connect(aboutBtn, SIGNAL(clicked()), this, SLOT(showAbout()));

        QPushButton *quitBtn = new QPushButton(i18n("Quit"), vbox);
        connect(quitBtn, SIGNAL(clicked()), qApp, SLOT(quit()));

        resize(300, 200);
    }

private slots:
    void showAbout() {
        QString msg = i18n("qt2-kde-mini Test Application\n\n"
                          "This is a test of the minimal KDE2 compatibility library.\n\n"
                          "Features tested:\n"
                          "- KApplication\n"
                          "- KConfig (persistent settings)\n"
                          "- i18n (internationalization stubs)\n"
                          "- KGlobal\n"
                          "- KAboutData");

        QMessageBox::information(this, i18n("About"), msg);
    }
};

#include "test-basic.moc"

int main(int argc, char **argv) {
    KAboutData aboutData("test-qt2kde", "qt2-kde-mini Test", "1.0",
                        "Test application for qt2-kde-mini library",
                        KAboutData::License_GPL);
    aboutData.addAuthor("Test Author", 0, "test@example.com");

    KCmdLineArgs::init(argc, argv, &aboutData);

    KApplication app(argc, argv);

    TestWindow *window = new TestWindow();
    app.setMainWidget(window);
    window->show();

    return app.exec();
}
