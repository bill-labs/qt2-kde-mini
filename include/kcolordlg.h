#ifndef KCOLORDLG_H
#define KCOLORDLG_H

#include <qcolordialog.h>
#include <qcolor.h>

// Compatibility wrapper - maps to QColorDialog
class KColorDialog {
public:
    static int getColor(QColor &color, QWidget *parent = 0) {
        QColor newColor = QColorDialog::getColor(color, parent);
        if (newColor.isValid()) {
            color = newColor;
            return QDialog::Accepted;
        }
        return QDialog::Rejected;
    }
};

#endif // KCOLORDLG_H
