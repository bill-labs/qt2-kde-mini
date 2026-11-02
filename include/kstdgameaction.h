#ifndef KSTDGAMEACTION_H
#define KSTDGAMEACTION_H

class KAction;
class KToggleAction;
class QObject;
class KActionCollection;

// Standard game actions (from libkdegames)
namespace KStdGameAction {
    enum StdGameAction {
        // Game menu
        New = 1, Load, Save, SaveAs, End, Pause, Highscores,
        Print, Quit,
        // Move menu
        Repeat, Undo, Redo, EndTurn,
        // Settings menu
        Carddecks
    };

    // Game menu
    KAction *gameNew(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *load(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *save(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *saveAs(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *end(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KToggleAction *pause(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *highscores(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *print(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *quit(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);

    // Move menu
    KAction *repeat(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *undo(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *redo(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);
    KAction *endTurn(const QObject *recvr, const char *slot, KActionCollection *parent, const char *name = 0);

    // Get standard name
    const char *stdName(StdGameAction id);
}

#endif // KSTDGAMEACTION_H
