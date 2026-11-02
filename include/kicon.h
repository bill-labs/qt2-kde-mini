#ifndef KICON_H
#define KICON_H

// KIcon size and group constants
class KIcon {
public:
    enum Group {
        NoGroup = -1,
        Desktop = 0,
        Toolbar,
        MainToolbar,
        Small,
        Panel,
        User
    };

    enum StdSizes {
        SizeSmall = 16,
        SizeMedium = 32,
        SizeLarge = 48
    };
};

#endif // KICON_H
