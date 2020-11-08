#ifndef MOORECHIPJAILBREAK_H
#define MOORECHIPJAILBREAK_H

#include "JailbreakAbstract.h"
#include "../../../libpandory/Environment.h"
#include "../../../libpandory/FsMounter.h"
#include "../../../libpandory/AndroidFilesystem.h"
#include "../../../libpandory/DD.h"

class MoorechipJailbreak : public JailbreakAbstract
{
protected:
    Environment environment;
    FsMounter fsMounter;
    AndroidFilesystem androidFilesystem;
    DD dd;
    bool mountFilesystem() override;
    bool copyFiles() override;
    bool copyBranding() override;
    bool setPermissions() override;
    bool finish() override;
};

#endif // MOORECHIPJAILBREAK_H
