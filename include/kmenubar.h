#ifndef KMENUBAR_H
#define KMENUBAR_H

#include <qmenubar.h>

// Simplified KMenuBar - just extends QMenuBar
class KMenuBar : public QMenuBar {
    Q_OBJECT

public:
    KMenuBar(QWidget *parent = 0, const char *name = 0)
        : QMenuBar(parent, name)
    {}

    virtual ~KMenuBar() {}
};

#endif // KMENUBAR_H
