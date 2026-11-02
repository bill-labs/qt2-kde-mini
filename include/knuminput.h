#ifndef KNUMINPUT_H
#define KNUMINPUT_H

#include <qspinbox.h>

// Simplified KIntNumInput - just wraps QSpinBox
class KIntNumInput : public QSpinBox {
    Q_OBJECT

public:
    KIntNumInput(QWidget *parent = 0, const char *name = 0)
        : QSpinBox(parent, name)
    {}

    KIntNumInput(int value, QWidget *parent = 0, const char *name = 0)
        : QSpinBox(parent, name)
    {
        setValue(value);
    }

    KIntNumInput(unsigned int value, QWidget *parent = 0, const char *name = 0)
        : QSpinBox(parent, name)
    {
        setValue((int)value);
    }

    void setRange(int min, int max) {
        QSpinBox::setMinValue(min);
        QSpinBox::setMaxValue(max);
    }

    void setLabel(const QString &label) {
        // Ignore label in simple version
    }
};

#endif // KNUMINPUT_H
