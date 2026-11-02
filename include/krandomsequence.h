#ifndef KRANDOMSEQUENCE_H
#define KRANDOMSEQUENCE_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include "kapp.h"

// Proper random number generator using system rand()
// but with better seeding
class KRandomSequence {
private:
    static bool& getInitialized() {
        static bool initialized = false;
        return initialized;
    }

    static void initRandom() {
        bool& initialized = getInitialized();
        if (!initialized) {
            struct timeval tv;
            gettimeofday(&tv, 0);
            unsigned int seed = (unsigned int)(tv.tv_sec ^ tv.tv_usec ^ (getpid() << 16));
            srand(seed);
            initialized = true;
        }
    }

public:
    KRandomSequence() {
        initRandom();
    }

    KRandomSequence(long seed) {
        getInitialized() = true;
        setSeed(seed);  // Use setSeed to handle seed=0 properly
    }

    void setSeed(long seed) {
        // Match KDE2 behavior: seed=0 means use KApplication::random()
        if (seed == 0) {
            seed = KApplication::random();
        }
        srand((unsigned int)seed);
    }

    // Generate random number 0..max-1
    long getLong(long max) {
        if (max <= 0) return 0;

        // Use multiple rand() calls for better distribution
        long r = (long)rand();
        if (max > RAND_MAX) {
            r = (r << 15) ^ (long)rand();
        }

        return r % max;
    }

    // Generate random double 0.0..1.0
    double getDouble() {
        return (double)rand() / (double)RAND_MAX;
    }

    // Generate random bool
    bool getBool() {
        return (rand() & 1) != 0;
    }
};

#endif // KRANDOMSEQUENCE_H
