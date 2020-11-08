#include "VideoDebricker.h"
#include <iostream>

void VideoDebricker::debrick() {
    std::cout << "Attempting video debrick. Let's go!" << std::endl;
    std::string restoreHDMI = "busybox dd if=/data/mtdblock0.img of=/dev/block/mtdblock0";
    restoreHDMI += " && busybox dd if=/data/mtdblock1.img of=/dev/block/mtdblock1";
    restoreHDMI += " && settings put global display_outputmode_auto 0";
    restoreHDMI += " && reboot";
    system(restoreHDMI.c_str());
}