#include <iostream>
#include "PandoryJailbreak.h"
#include "Jailbreak/TrimuiJailbreak.h"
#include "Jailbreak/MoorechipJailbreak.h"

int PandoryJailbreak::main() {
    if (environment.isTrimUiFirmware()) {
        TrimuiJailbreak jb;
        jb.jailbreak();
    } else if (environment.isMoorechipFirmware()) {
        MoorechipJailbreak jb;
        jb.jailbreak();
    }
    return 0;
}
