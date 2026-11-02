#ifndef KDEBUG_H
#define KDEBUG_H

#include <qstring.h>
#include <iostream>

// Simplified debug output - maps to cout/cerr
class kdbgstream {
public:
    kdbgstream(std::ostream &stream) : m_stream(stream) {}
    ~kdbgstream() { m_stream << std::endl; }

    kdbgstream &operator<<(const QString &str) {
        m_stream << str.latin1();
        return *this;
    }

    kdbgstream &operator<<(const char *str) {
        m_stream << str;
        return *this;
    }

    kdbgstream &operator<<(int i) {
        m_stream << i;
        return *this;
    }

    kdbgstream &operator<<(double d) {
        m_stream << d;
        return *this;
    }

    // Support for endl and other manipulators
    kdbgstream &operator<<(std::ostream& (*pf)(std::ostream&)) {
        m_stream << pf;
        return *this;
    }

private:
    std::ostream &m_stream;
};

// Debug output functions
inline kdbgstream kdDebug(int area = 0) { return kdbgstream(std::cout); }
inline kdbgstream kdWarning(int area = 0) { return kdbgstream(std::cerr); }
inline kdbgstream kdError(int area = 0) { return kdbgstream(std::cerr); }
inline kdbgstream kdFatal(int area = 0) { return kdbgstream(std::cerr); }

#endif // KDEBUG_H
