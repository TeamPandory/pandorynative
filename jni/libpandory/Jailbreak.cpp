#include "Jailbreak.h"
#include <fstream>

bool Jailbreak::isAspectSwitchActive() {
    return aspectRatioFix;
}

Jailbreak::Jailbreak() {
    std::ifstream meta("/data/meta.bin");
    std::ifstream res("/data/res.bin");
    std::string metaString, resString;
    edition = 0;
    if (meta.is_open()) {
        getline(meta, metaString);
        if (metaString == "/dev/block/data") {
            edition = 1;
        }
        meta.close();
    }
    if (res.is_open()) {
        getline(res, resString);
        if (resString.substr(0, 3) == "4:3") {
            aspectRatioFix = false;
        }
    }
}

bool Jailbreak::isUltimate() {
    return (edition == 1);
}
