#ifndef KAUDIOPLAYER_H
#define KAUDIOPLAYER_H

#include <qstring.h>

// Simplified KAudioPlayer - stub implementation (no actual sound playback)
class KAudioPlayer {
public:
    // Play a sound file
    static void play(const QString &filename) {
        // Stub - do nothing
        // In a real implementation this would use Qt sound or system audio
    }

    // Check if audio is available
    static bool audioAvailable() {
        return false; // Always return false in stub
    }
};

#endif // KAUDIOPLAYER_H
