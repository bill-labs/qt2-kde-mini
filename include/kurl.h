#ifndef KURL_H
#define KURL_H

#include <qstring.h>

// Simplified KURL - just wraps QString
class KURL {
public:
    KURL() {}
    KURL(const QString &url) : m_url(url) {}
    KURL(const KURL &other) : m_url(other.m_url) {}

    QString url() const { return m_url; }
    QString path() const { return m_url; }
    bool isEmpty() const { return m_url.isEmpty(); }

    void addPath(const QString &p) { m_url += "/" + p; }
    void setQuery(const QString &q) { m_query = q; }
    QString query() const { return m_query; }

    static QString encode_string(const QString &s) { return s; }

private:
    QString m_url;
    QString m_query;
};

#endif // KURL_H
