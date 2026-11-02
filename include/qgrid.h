#ifndef QGRID_H
#define QGRID_H

#include <qwidget.h>
#include <qgridlayout.h>

// Qt2's QGrid - simple grid layout widget
class QGrid : public QWidget {
public:
    QGrid(int cols, QWidget *parent = 0, const char *name = 0)
        : QWidget(parent, name)
    {
        m_layout = new QGridLayout(this, -1, cols);
    }

    QGrid(int cols, Orientation orient, QWidget *parent = 0, const char *name = 0)
        : QWidget(parent, name)
    {
        (void)orient; // ignore
        m_layout = new QGridLayout(this, -1, cols);
    }

private:
    QGridLayout *m_layout;
};

#endif // QGRID_H
