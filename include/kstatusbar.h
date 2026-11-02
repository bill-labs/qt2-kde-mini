#ifndef KSTATUSBAR_H
#define KSTATUSBAR_H

#include <qstatusbar.h>
#include <qlabel.h>

// Simplified KStatusBar - extends QStatusBar
class KStatusBar : public QStatusBar {
    Q_OBJECT

public:
    KStatusBar(QWidget *parent = 0, const char *name = 0)
        : QStatusBar(parent, name)
    {}

    virtual ~KStatusBar() {}

    // KDE compatibility methods
    void insertItem(const QString &text, int id, int stretch = 0) {
        // Simple implementation - just add a label
        addWidget(new QLabel(text, this), stretch);
    }

    void changeItem(const QString &text, int id) {
        message(text);
    }
};

#endif // KSTATUSBAR_H
