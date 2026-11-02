# qt2-kde-mini

Minimal KDE2 compatibility library for Qt 2.3.2

## Purpose

This library provides simplified implementations of KDE2 classes to allow porting KDE2 applications (especially games from kdegames-2.2.2) to pure Qt2, removing dependency on kdelibs.

## Features

### Fully Implemented

**Core Classes:**
- **KApplication** - Wrapper around QApplication with config support
- **KConfig** - Simple INI-file based configuration
- **KGlobal** - Global object access
- **KAboutData** - Application metadata (simplified)
- **KCmdLineArgs** - Command line parsing (stub)
- **i18n stubs** - All internationalization stripped, English-only

**UI Components:**
- **KMainWindow** - Main window (simplified, no XML UI)
- **KMenuBar** - Menu bar (extends QMenuBar)
- **KToolBar** - Tool bar (extends QToolBar)
- **KStatusBar** - Status bar (extends QStatusBar)
- **KAccel** - Keyboard accelerators

**Action System:**
- **KAction** - Base action class
- **KToggleAction** - Toggle (checkbox) action
- **KRadioAction** - Radio button action
- **KStdAction** - Standard application actions (File, Edit, Settings, Help menus)
- **KStdGameAction** - Standard game actions (New Game, Pause, Highscores, etc.)

### Not Implemented (not needed for games)

- XML UI framework
- Session management
- DCOP, KParts
- Full internationalization
- KDE standard directories

## Building

```bash
make
```

This creates `libqt2kdemini.so` shared library.

## Usage

Include headers:
```cpp
#include <kapp.h>
#include <kconfig.h>
#include <klocale.h>
```

Link against the library:
```bash
g++ -Iqt2-kde-mini/include -Lqt2-kde-mini -lqt2kdemini yourapp.cpp
```

## Differences from KDE2

- No XML UI system - menus/toolbars must be created programmatically
- No session management
- No internationalization (i18n is a no-op macro)
- Simplified configuration (no KDE standard dirs)
- No DCOP, KParts, or other advanced KDE features

## License

GPL v2 - Same as original KDE libraries


## Imported source snapshot

# qt2-kde-mini

Minimal KDE2 API compatibility library for Qt 2.

Source release: [Novell UnixWare Revival Pack XMAS'25](https://archive.org/details/novell-unixware-revival-pack-xmas-25).

Source snapshot dated 2025-12-25.

## Building

Use the included Makefile, which targets historical UnixWare and its libraries. This import has not been build-tested.

## Provenance and rights

**License: GPL-2.0-only.** See [LICENSE](LICENSE). Original upstream notices remain in source files.

See [SOURCE-ORIGIN.md](SOURCE-ORIGIN.md) for source archive hashes, attribution, and additional details.
