#ifndef KCOLORBTN_H
#define KCOLORBTN_H

#include <qpushbutton.h>
#include <qcolor.h>

// Simplified color button - just a QPushButton
class KColorButton : public QPushButton {
    Q_OBJECT

public:
    KColorButton(QWidget *parent = 0, const char *name = 0)
        : QPushButton(parent, name), m_color(Qt::black)
    {}

    KColorButton(const QColor &color, QWidget *parent = 0, const char *name = 0)
        : QPushButton(parent, name), m_color(color)
    {}

    QColor color() const { return m_color; }
    void setColor(const QColor &color) { m_color = color; }

signals:
    void changed(const QColor &);

private:
    QColor m_color;
};

#endif // KCOLORBTN_H
