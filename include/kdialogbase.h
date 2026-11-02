#ifndef KDIALOGBASE_H
#define KDIALOGBASE_H

#include <qdialog.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qframe.h>
#include <qvbox.h>
#include <stdio.h>

// Simplified KDialogBase - basic dialog with buttons
class KDialogBase : public QDialog {
    Q_OBJECT

public:
    enum ButtonCode {
        None = 0,
        Ok = 1,
        Cancel = 2,
        Yes = 4,
        No = 8,
        Apply = 16,
        Default = 32,
        Close = 64,
        Help = 128
    };

    enum DialogType {
        Plain,
        Tabbed,
        IconList
    };

    KDialogBase(QWidget *parent = 0, const char *name = 0,
                bool modal = true, const QString &caption = QString::null,
                int buttonMask = Ok|Cancel, ButtonCode defaultButton = Ok)
        : QDialog(parent, name, modal), m_contentWidget(0), m_okButton(0), m_defaultButton(0)
    {
        if (!caption.isEmpty()) setCaption(caption);

        m_layout = new QVBoxLayout(this, 10);
        m_buttonLayout = new QHBoxLayout();
        m_layout->addStretch();
        m_layout->addLayout(m_buttonLayout);

        if (buttonMask & Ok) {
            QPushButton *btn = new QPushButton("OK", this);
            m_buttonLayout->addWidget(btn);
            m_okButton = btn;
            connect(btn, SIGNAL(clicked()), SLOT(accept()));
        }
        if (buttonMask & Cancel) {
            QPushButton *btn = new QPushButton("Cancel", this);
            m_buttonLayout->addWidget(btn);
            connect(btn, SIGNAL(clicked()), SLOT(reject()));
        }
        if (buttonMask & Default) {
            QPushButton *btn = new QPushButton("Default", this);
            m_buttonLayout->addWidget(btn);
            m_defaultButton = btn;
            connect(btn, SIGNAL(clicked()), SLOT(slotDefault()));
        }
    }

    KDialogBase(int dialogType, const QString &caption, int buttonMask,
                ButtonCode defaultButton, QWidget *parent = 0,
                const char *name = 0, bool modal = true, bool separator = false)
        : QDialog(parent, name, modal), m_contentWidget(0), m_okButton(0), m_defaultButton(0)
    {
        (void)dialogType; // ignore for now
        (void)defaultButton; // ignore for now
        (void)separator; // ignore for now
        if (!caption.isEmpty()) setCaption(caption);

        m_layout = new QVBoxLayout(this, 10);
        m_buttonLayout = new QHBoxLayout();
        // Don't add stretch here - content will be added before buttons
        m_layout->addLayout(m_buttonLayout);

        if (buttonMask & Ok) {
            QPushButton *btn = new QPushButton("OK", this);
            m_buttonLayout->addWidget(btn);
            m_okButton = btn;
            connect(btn, SIGNAL(clicked()), SLOT(accept()));
        }
        if (buttonMask & Cancel) {
            QPushButton *btn = new QPushButton("Cancel", this);
            m_buttonLayout->addWidget(btn);
            connect(btn, SIGNAL(clicked()), SLOT(reject()));
        }
        if (buttonMask & Default) {
            QPushButton *btn = new QPushButton("Default", this);
            m_buttonLayout->addWidget(btn);
            m_defaultButton = btn;
            connect(btn, SIGNAL(clicked()), SLOT(slotDefault()));
        }
        if (buttonMask & Close) {
            QPushButton *btn = new QPushButton("Close", this);
            m_buttonLayout->addWidget(btn);
            connect(btn, SIGNAL(clicked()), SLOT(accept()));
        }
    }

    virtual ~KDialogBase() {}

    void enableButton(ButtonCode button, bool enable) {
        if (button == Ok && m_okButton) {
            m_okButton->setEnabled(enable);
        } else if (button == Default && m_defaultButton) {
            m_defaultButton->setEnabled(enable);
        }
    }

    QFrame *addPage(const QString &/*itemName*/, const QString &/*header*/ = QString::null,
                     const QPixmap &/*pixmap*/ = QPixmap()) {
        // Simplified - return a QFrame for content
        if (!m_contentWidget) {
            m_contentWidget = new QFrame(this);
            // Insert content at position 0 (before button layout which is at the end)
            m_layout->insertWidget(0, m_contentWidget, 1);  // stretch factor = 1
        }
        return (QFrame*)m_contentWidget;
    }

    QWidget *plainPage() {
        // Return plain content widget
        if (!m_contentWidget) {
            m_contentWidget = new QFrame(this);
            // Insert content at position 0 (before button layout)
            m_layout->insertWidget(0, m_contentWidget, 1);  // stretch factor = 1
        }
        return (QWidget*)m_contentWidget;
    }

    int spacingHint() const { return 10; }

    QVBox *addVBoxPage(const QString &/*itemName*/, const QString &/*header*/ = QString::null, const QPixmap &/*pixmap*/ = QPixmap()) {
        // Simplified - create and return a VBox
        if (!m_contentWidget) {
            m_contentWidget = new QFrame(this);
            // Add a layout to the content widget so children will be visible
            new QVBoxLayout(m_contentWidget, 10);
            // Insert content at position 0 (before button layout)
            m_layout->insertWidget(0, m_contentWidget, 1);  // stretch factor = 1
        }
        // Create a VBox as child of content widget
        QVBox *vbox = new QVBox(m_contentWidget);
        vbox->setMinimumSize(400, 300);  // Ensure it has some size
        return vbox;
    }

    void enableButtonSeparator(bool) {}

    int pageIndex(QWidget *) const { return 0; }
    void showPage(int) {}

protected slots:
    virtual void slotDefault() {}

protected:
    QVBoxLayout *m_layout;
    QHBoxLayout *m_buttonLayout;
    QFrame *m_contentWidget;
    QPushButton *m_okButton;
    QPushButton *m_defaultButton;
};

#endif // KDIALOGBASE_H
