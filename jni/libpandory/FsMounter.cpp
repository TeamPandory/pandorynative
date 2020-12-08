#include "FsMounter.h"

bool FsMounter::mount(const std::string &device, const std::string &mountPoint) {
    process.exec("busybox mount " + device + " " + mountPoint);
    return true;
}

bool FsMounter::unmount(const std::string& device)
{
    process.exec("busybox umount " + device);
    return true;
}

bool FsMounter::bindMount(const std::string &device, const std::string &mountPoint) {
    process.exec("busybox mount -o bind " + device + " " + mountPoint);
    return false;
}