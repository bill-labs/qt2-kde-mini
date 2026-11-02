#ifndef KURLLABEL_H
#define KURLLABEL_H

#include <qlabel.h>
#include <qstring.h>

// Stub - URL label widget
class KURLLabel : public QLabel {
    Q_OBJECT
public:
    KURLLabel(QWidget *parent = 0, const char *name = 0) : QLabel(parent, name) {}
    KURLLabel(const QString &url, const QString &text, QWidget *parent = 0, const char *name = 0)
        : QLabel(text, parent, name), m_url(url) {}
    
    void setURL(const QString &url) { m_url = url; }
    QString url() const { return m_url; }
    
signals:
    void leftClickedURL(const QString &);
    
private:
    QString m_url;
};

#endif // KURLLABEL_H
