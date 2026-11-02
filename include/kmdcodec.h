#ifndef KMDCODEC_H
#define KMDCODEC_H

#include <qstring.h>
#include <qcstring.h>

// Stub for MD5 encoding
class KMD5 {
public:
    KMD5() {}
    KMD5(const QString &) {}
    void update(const QCString &) {}
    void update(const char *, int) {}
    QCString hexDigest() const { return QCString("0000000000000000"); }
};

#endif // KMDCODEC_H
