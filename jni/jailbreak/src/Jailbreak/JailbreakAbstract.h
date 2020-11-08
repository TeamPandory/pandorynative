#ifndef JAILBREAKABSTRACT_H
#define JAILBREAKABSTRACT_H

#include <string>
#include "../../../libpandory/AndroidFilesystem.h"
#include "../../../libpandory/Process.h"
#include "../../../libpandory/TimeTools.h"

class JailbreakAbstract
{
protected:
    AndroidFilesystem androidFilesystem;
    Process process;
    TimeTools timeTools;
    virtual bool init();
    virtual bool mountFilesystem();
    virtual bool copyFiles();
    virtual bool copyBranding();
    virtual bool setPermissions();
    virtual bool finish();
    virtual bool notify(const std::string &msg);
public:
    bool jailbreak();
};

#endif // JAILBREAKABSTRACT_H
