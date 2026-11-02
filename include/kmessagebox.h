#ifndef KMESSAGEBOX_H
#define KMESSAGEBOX_H

#include <qmessagebox.h>
#include <qstring.h>

class QWidget;

// Simplified KMessageBox - wrapper around QMessageBox
class KMessageBox {
public:
    // Information dialog
    static void information(QWidget *parent, const QString &text,
                           const QString &caption = QString::null) {
        QString cap = caption.isEmpty() ? QString("Information") : caption;
        QMessageBox::information(parent, cap, text);
    }

    // Error dialog
    static void error(QWidget *parent, const QString &text,
                     const QString &caption = QString::null) {
        QString cap = caption.isEmpty() ? QString("Error") : caption;
        QMessageBox::critical(parent, cap, text);
    }

    // Warning dialog
    static void sorry(QWidget *parent, const QString &text,
                     const QString &caption = QString::null) {
        QString cap = caption.isEmpty() ? QString("Sorry") : caption;
        QMessageBox::warning(parent, cap, text);
    }

    // Question dialog (Yes/No)
    static int questionYesNo(QWidget *parent, const QString &text,
                            const QString &caption = QString::null) {
        QString cap = caption.isEmpty() ? QString("Question") : caption;
        int ret = QMessageBox::warning(parent, cap, text,
                                      QMessageBox::Yes | QMessageBox::Default,
                                      QMessageBox::No | QMessageBox::Escape);
        return (ret == QMessageBox::Yes) ? 3 : 4; // KDE Yes=3, No=4
    }

    // Continue/Cancel dialog
    static int warningContinueCancel(QWidget *parent, const QString &text,
                                    const QString &caption = QString::null) {
        QString cap = caption.isEmpty() ? QString("Warning") : caption;
        int ret = QMessageBox::warning(parent, cap, text,
                                      QMessageBox::Ok | QMessageBox::Default,
                                      QMessageBox::Cancel | QMessageBox::Escape);
        return (ret == QMessageBox::Ok) ? 5 : 2; // KDE Continue=5, Cancel=2
    }
};

#endif // KMESSAGEBOX_H
