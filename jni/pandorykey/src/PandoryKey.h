#ifndef PANDORYKEY_PANDORYKEY_H
#define PANDORYKEY_PANDORYKEY_H

#include "../../libpandory/ResolutionSwitcher.h"
#include "../../libpandory/VideoDebricker.h"
#include "../../libpandory/VirtualKeyboard.h"
#include "../../libpandory/Android.h"
#include "../../libpandory/AppDetect.h"
#include "../../libpandory/MooreChip.h"
#include "../../libpandory/PandoraController.h"
#include "../../libpandory/TimeTools.h"
#include "../../libpandory/Jailbreak.h"
#include "../../libpandory/ShellEnabler.h"
#include "../../libpandory/Environment.h"
#include "../../libpandory/Fs.h"
#include "../../libpandory/Process.h"

class PandoryKey {
protected:
    ResolutionSwitcher resolutionSwitcher;
    VideoDebricker videoDebricker;
    Android android;
    VirtualKeyboard virtualKeyboard;
    MooreChip mooreChip;
    PandoraController pandoraController;
    TimeTools timeTools;
    AppDetect appDetect;
    Jailbreak jailbreak;
    ShellEnabler shellEnabler;
    Environment environment;
    Fs fs;
    Process process;
public:
    int main();
};

#endif //PANDORYKEY_PANDORYKEY_H
