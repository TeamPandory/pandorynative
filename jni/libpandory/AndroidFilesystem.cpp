#include <cstdlib>
#include "AndroidFilesystem.h"

bool AndroidFilesystem::remountSystemReadWrite() {
    system("mount -o rw,remount /system");
    return true;
}

bool AndroidFilesystem::setPermissions(const std::string &path, int permissions) {
    std::string cmd = "chmod " + std::to_string(permissions) + " " + path;
    system(cmd.c_str());
    return false;
}

bool AndroidFilesystem::setOwner(const std::string &path, const std::string &owner) {
    std::string cmd = "chown " + owner + " " + path;
    system(cmd.c_str());
    return false;
}
