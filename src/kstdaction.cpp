#include "kstdaction.h"
#include "kaction.h"
#include "kactioncollection.h"
#include <qstring.h>
#include <qfile.h>

namespace KStdAction {

// Helper to get icon path
static QString iconPath(const char* iconName) {
#ifdef PREFIX
    // Always use PREFIX path when compiled with PREFIX
    return QString(PREFIX) + "/share/qt2-kde-mini/icons/" + iconName;
#else
    // Development mode - use relative path
    return QString("../qt2-kde-mini/icons/") + iconName;
#endif
}

// Standard action names
const char *stdName(StdAction id) {
    switch (id) {
        case New: return "file_new";
        case Open: return "file_open";
        case Save: return "file_save";
        case SaveAs: return "file_save_as";
        case Print: return "file_print";
        case Quit: return "file_quit";
        case Undo: return "edit_undo";
        case Redo: return "edit_redo";
        case Cut: return "edit_cut";
        case Copy: return "edit_copy";
        case Paste: return "edit_paste";
        case ShowMenubar: return "options_show_menubar";
        case ShowToolbar: return "options_show_toolbar";
        case ShowStatusbar: return "options_show_statusbar";
        case Preferences: return "options_configure";
        case KeyBindings: return "options_configure_keybinding";
        case Help: return "help_contents";
        case AboutApp: return "help_about_app";
        case AboutKDE: return "help_about_kde";
        default: return "";
    }
}

// File menu

KAction *openNew(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&New", 0, recvr, slot, parent,
                      name ? name : stdName(New));
}

KAction *open(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Open...", 0, recvr, slot, parent,
                      name ? name : stdName(Open));
}

KAction *save(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Save", 0, recvr, slot, parent,
                      name ? name : stdName(Save));
}

KAction *saveAs(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("Save &As...", 0, recvr, slot, parent,
                      name ? name : stdName(SaveAs));
}

KAction *print(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Print...", 0, recvr, slot, parent,
                      name ? name : stdName(Print));
}

KAction *quit(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Quit", 0, recvr, slot, parent,
                      name ? name : stdName(Quit));
}

// Edit menu

KAction *undo(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Undo", iconPath("hi16-action-undo.png"), 0, recvr, slot, parent,
                      name ? name : stdName(Undo));
}

KAction *redo(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Redo", iconPath("hi16-action-redo.png"), 0, recvr, slot, parent,
                      name ? name : stdName(Redo));
}

KAction *cut(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("Cu&t", 0, recvr, slot, parent,
                      name ? name : stdName(Cut));
}

KAction *copy(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Copy", 0, recvr, slot, parent,
                      name ? name : stdName(Copy));
}

KAction *paste(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Paste", 0, recvr, slot, parent,
                      name ? name : stdName(Paste));
}

// Settings menu

KToggleAction *showMenubar(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    KToggleAction *action = new KToggleAction("Show &Menubar", 0, recvr, slot, parent,
                                              name ? name : stdName(ShowMenubar));
    action->setChecked(true);
    return action;
}

KToggleAction *showToolbar(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    KToggleAction *action = new KToggleAction("Show &Toolbar", 0, recvr, slot, parent,
                                              name ? name : stdName(ShowToolbar));
    action->setChecked(true);
    return action;
}

KToggleAction *showStatusbar(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    KToggleAction *action = new KToggleAction("Show St&atusbar", 0, recvr, slot, parent,
                                              name ? name : stdName(ShowStatusbar));
    action->setChecked(true);
    return action;
}

KAction *preferences(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Preferences...", 0, recvr, slot, parent,
                      name ? name : stdName(Preferences));
}

KAction *keyBindings(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("Configure &Key Bindings...", 0, recvr, slot, parent,
                      name ? name : stdName(KeyBindings));
}

// Help menu

KAction *help(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Help", 0, recvr, slot, parent,
                      name ? name : stdName(Help));
}

KAction *aboutApp(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&About", 0, recvr, slot, parent,
                      name ? name : stdName(AboutApp));
}

KAction *aboutKDE(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("About &KDE", 0, recvr, slot, parent,
                      name ? name : stdName(AboutKDE));
}

// Other

KAction *find(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Find...", 0, recvr, slot, parent, name);
}

KAction *close(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Close", 0, recvr, slot, parent, name);
}

} // namespace KStdAction
