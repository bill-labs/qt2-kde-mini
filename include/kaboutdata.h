#ifndef KABOUTDATA_H
#define KABOUTDATA_H

#include <qstring.h>

// Simplified KAboutData - just stores basic info
class KAboutData {
public:
    enum LicenseKey {
        License_GPL,
        License_LGPL,
        License_BSD,
        License_Artistic
    };

    KAboutData(const char *appName,
               const char *programName,
               const char *version,
               const char *shortDescription = 0,
               int licenseType = License_GPL,
               const char *copyrightStatement = 0,
               const char *text = 0,
               const char *homePageAddress = 0,
               const char *bugsEmailAddress = 0)
        : m_appName(appName),
          m_programName(programName),
          m_version(version),
          m_shortDescription(shortDescription ? shortDescription : ""),
          m_copyrightStatement(copyrightStatement ? copyrightStatement : ""),
          m_license(licenseType)
    {}

    void addAuthor(const char *name, const char *task = 0, const char *email = 0) {}
    void addCredit(const char *name, const char *task = 0, const char *email = 0) {}

    const char *appName() const { return m_appName; }
    const char *programName() const { return m_programName; }
    const char *version() const { return m_version; }
    QString shortDescription() const { return m_shortDescription; }
    QString copyrightStatement() const { return m_copyrightStatement; }

private:
    const char *m_appName;
    const char *m_programName;
    const char *m_version;
    QString m_shortDescription;
    QString m_copyrightStatement;
    int m_license;
};

#endif // KABOUTDATA_H
