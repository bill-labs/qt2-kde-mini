#include "kstdgameaction.h"
#include "kaction.h"
#include "kactioncollection.h"
#include <qstring.h>
#include <qfile.h>

namespace KStdGameAction {

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

const char *stdName(StdGameAction id) {
    switch (id) {
        case New: return "game_new";
        case Load: return "game_load";
        case Save: return "game_save";
        case SaveAs: return "game_save_as";
        case End: return "game_end";
        case Pause: return "game_pause";
        case Highscores: return "game_highscores";
        case Print: return "game_print";
        case Quit: return "game_quit";
        case Repeat: return "move_repeat";
        case Undo: return "move_undo";
        case Redo: return "move_redo";
        case EndTurn: return "move_end_turn";
        default: return "";
    }
}

// Game menu

KAction *gameNew(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&New Game", iconPath("hi16-action-filenew.png"), 0, recvr, slot, parent,
                      name ? name : stdName(New));
}

KAction *load(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Load...", iconPath("hi16-action-reload.png"), 0, recvr, slot, parent,
                      name ? name : stdName(Load));
}

KAction *save(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Save", iconPath("hi16-action-filesave.png"), 0, recvr, slot, parent,
                      name ? name : stdName(Save));
}

KAction *saveAs(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("Save &As...", 0, recvr, slot, parent,
                      name ? name : stdName(SaveAs));
}

KAction *end(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&End Game", 0, recvr, slot, parent,
                      name ? name : stdName(End));
}

KToggleAction *pause(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KToggleAction("&Pause", iconPath("hi16-action-player_pause.png"), 0, recvr, slot, parent,
                            name ? name : stdName(Pause));
}

KAction *highscores(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("Show &Highscores", 0, recvr, slot, parent,
                      name ? name : stdName(Highscores));
}

KAction *print(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Print...", 0, recvr, slot, parent,
                      name ? name : stdName(Print));
}

KAction *quit(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Quit", iconPath("hi16-action-exit.png"), 0, recvr, slot, parent,
                      name ? name : stdName(Quit));
}

// Move menu

KAction *repeat(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("Repeat Move", 0, recvr, slot, parent,
                      name ? name : stdName(Repeat));
}

KAction *undo(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Undo Move", 0, recvr, slot, parent,
                      name ? name : stdName(Undo));
}

KAction *redo(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&Redo Move", 0, recvr, slot, parent,
                      name ? name : stdName(Redo));
}

KAction *endTurn(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name) {
    return new KAction("&End Turn", 0, recvr, slot, parent,
                      name ? name : stdName(EndTurn));
}

} // namespace KStdGameAction
