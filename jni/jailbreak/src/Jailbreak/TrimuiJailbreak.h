#ifndef TRIMUIJAILBREAK_H
#define TRIMUIJAILBREAK_H

#include "TrimuiJailbreak.h"
#include "JailbreakAbstract.h"
#include "../../../libpandory/Notifier.h"
#include "../../../libpandory/Process.h"
#include "../../../libpandory/AndroidFilesystem.h"
#include "../../../libpandory/TimeTools.h"
#include "../../../libpandory/FsMounter.h"

class TrimuiJailbreak : public JailbreakAbstract
{
protected:
	bool createSystemLog();
    Notifier notifier;
    Process process;
    AndroidFilesystem androidFilesystem;
    TimeTools timeTools;
    FsMounter fsMounter;
    bool mountFilesystem() override;
    bool copyFiles() override;
    bool copyBranding() override;
    bool init() override;
    bool notify(const std::string& msg) override;
    bool finish() override;
    bool setPermissions() override;
};

#endif // TRIMUIJAILBREAK_H
