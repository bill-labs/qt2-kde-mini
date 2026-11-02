#include "kseparator.h"

KSeparator::KSeparator(QWidget *parent, const char *name)
    : QFrame(parent, name)
{
    setFrameStyle(QFrame::HLine | QFrame::Sunken);
    setMinimumHeight(2);
    setMaximumHeight(2);
}

KSeparator::KSeparator(Orientation orientation, QWidget *parent, const char *name)
    : QFrame(parent, name)
{
    if (orientation == Horizontal) {
        setFrameStyle(QFrame::HLine | QFrame::Sunken);
        setMinimumHeight(2);
        setMaximumHeight(2);
    } else {
        setFrameStyle(QFrame::VLine | QFrame::Sunken);
        setMinimumWidth(2);
        setMaximumWidth(2);
    }
}
