#ifndef PANDORYKEY_JAILBREAK_H
#define PANDORYKEY_JAILBREAK_H


class Jailbreak {
protected:
    int edition = 0;
    bool aspectRatioFix = true;

public:
    Jailbreak();
    bool isUltimate();
    bool isAspectSwitchActive();
};


#endif //PANDORYKEY_JAILBREAK_H
