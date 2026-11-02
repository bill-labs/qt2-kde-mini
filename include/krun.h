#ifndef KRUN_H
#define KRUN_H

#include <qstring.h>

class KURL;

// File open handler stub
class KFileOpenWithHandler {};

// Stub - run command/URL
class KRun {
public:
    KRun() {}
    KRun(const KURL &) {}
    static void runURL(const KURL &, const QString &) {}
};

#endif // KRUN_H
