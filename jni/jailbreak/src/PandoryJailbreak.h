#ifndef PANDORYKEY_PANDORYJAILBREAK_H
#define PANDORYKEY_PANDORYJAILBREAK_H

#include "../../libpandory/AndroidFilesystem.h"
#include "../../libpandory/Fs.h"
#include "../../libpandory/DD.h"
#include "../../libpandory/Process.h"
#include "../../libpandory/AndroidProperties.h"
#include "../../libpandory/TimeTools.h"
#include "../../libpandory/FsMounter.h"
#include "../../libpandory/Environment.h"
#include "../../libpandory/Notifier.h"

class PandoryJailbreak {
protected:
    AndroidFilesystem androidFilesystem;
    Environment environment;
    FsMounter fsMounter;
    TimeTools timeTools;
    DD dd;
    Process process;
    Notifier notifier;
public:
    int main();
};

#endif //PANDORYKEY_PANDORYJAILBREAK_H
