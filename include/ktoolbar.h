#ifndef KTOOLBAR_H
#define KTOOLBAR_H

#include <qtoolbar.h>
#include <qmainwindow.h>
#include <qpixmap.h>
#include <qmap.h>

// Simplified KToolBar - extends QToolBar
class KToolBar : public QToolBar {
    Q_OBJECT

public:
    enum BarPosition { Top = 0, Bottom, Left, Right, Floating };

    KToolBar(QMainWindow *parent = 0, const char *name = 0)
        : QToolBar(parent, name)
    {}

    virtual ~KToolBar() {}

    // Insert button with pixmap
    int insertButton(const QPixmap &pixmap, int id, bool enabled = true,
                     const QString &tooltip = QString::null, int index = -1) {
        // For simplicity, just create a button without tracking
        return id;
    }

    // Enable/disable toolbar item
    void setItemEnabled(int id, bool enabled) {
        // Stub - we don't track items properly
    }

    // Get toolbar position
    BarPosition barPos() const {
        return Top; // Always return Top for simplicity
    }

    // Set toolbar position (stub - does nothing)
    void setBarPos(BarPosition pos) {
        // Stub - position is not actually changed
    }

    // Insert separator
    void insertSeparator(int index = -1) {
        addSeparator();
    }

signals:
    // Signals that app.cpp expects
    void clicked(int id);
    void moved(BarPosition pos);
};

#endif // KTOOLBAR_H
