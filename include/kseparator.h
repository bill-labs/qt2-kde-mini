#ifndef KSEPARATOR_H
#define KSEPARATOR_H

#include <qframe.h>

// Simplified KSeparator - just a horizontal or vertical line
class KSeparator : public QFrame {
    Q_OBJECT

public:
    enum Orientation { Horizontal = 0, Vertical };

    KSeparator(QWidget *parent = 0, const char *name = 0);
    KSeparator(Orientation orientation, QWidget *parent = 0, const char *name = 0);
    virtual ~KSeparator() {}
};

#endif // KSEPARATOR_H
