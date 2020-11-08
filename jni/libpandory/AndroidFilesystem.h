#ifndef PANDORYJAILBREAK_ANDROIDFILESYSTEM_H
#define PANDORYJAILBREAK_ANDROIDFILESYSTEM_H

#include <string>

class AndroidFilesystem {
public:
    bool remountSystemReadWrite();
    bool setPermissions(const std::string &path, int permissions);
    bool setOwner(const std::string &path, const std::string &owner);
};

#endif //PANDORYJAILBREAK_ANDROIDFILESYSTEM_H
