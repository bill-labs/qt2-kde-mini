#ifndef KSTDACTION_H
#define KSTDACTION_H

class KAction;
class KToggleAction;
class QObject;
class KActionCollection;

// Standard actions for applications
namespace KStdAction {
    enum StdAction {
        New, Open, OpenRecent, Save, SaveAs, Revert, Close,
        Print, PrintPreview, Mail, Quit,
        Undo, Redo, Cut, Copy, Paste, SelectAll, Deselect, Find, FindNext, FindPrev, Replace,
        ActualSize, FitToPage, FitToWidth, FitToHeight, ZoomIn, ZoomOut, Zoom,
        Redisplay, Up, Back, Forward, Home, Prior, Next, Goto, GotoPage, GotoLine,
        FirstPage, LastPage, AddBookmark, EditBookmarks,
        Spelling, ShowMenubar, ShowToolbar, ShowStatusbar,
        SaveOptions, KeyBindings, Preferences, ConfigureToolbars,
        Help, HelpContents, WhatsThis, ReportBug, AboutApp, AboutKDE,
        TipofDay, ConfigureNotifications, FullScreen, Clear,
        PasteText, SwitchApplicationLanguage
    };

    // File menu
    KAction *openNew(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *open(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *save(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *saveAs(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *print(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *quit(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);

    // Edit menu
    KAction *undo(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *redo(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *cut(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *copy(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *paste(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);

    // Settings menu
    KToggleAction *showMenubar(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KToggleAction *showToolbar(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KToggleAction *showStatusbar(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *preferences(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *keyBindings(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);

    // Help menu
    KAction *help(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *aboutApp(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *aboutKDE(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);

    // Other
    KAction *find(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *close(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);

    // Get standard name for action
    const char *stdName(StdAction id);
}

#endif // KSTDACTION_H
