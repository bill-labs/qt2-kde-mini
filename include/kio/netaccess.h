#ifndef KIO_NETACCESS_H
#define KIO_NETACCESS_H

#include <qstring.h>

class KURL;
class QWidget;

// Stub for network access
namespace KIO {
    class NetAccess {
    public:
        static bool download(const KURL &, const QString &, QWidget * = 0) { return false; }
        static void removeTempFile(const QString &) {}
    };
}

#endif // KIO_NETACCESS_H
