#ifndef KPRINTER_H
#define KPRINTER_H

#include <qprinter.h>

// Stub - printer wrapper
class KPrinter : public QPrinter {
public:
    KPrinter() : QPrinter() {}
    virtual ~KPrinter() {}

    // Show print dialog (stub - always return false to skip printing)
    bool setup(QWidget * = 0) { return false; }
};

#endif // KPRINTER_H
