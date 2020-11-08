#include "AppDetect.h"

#include <iostream>

bool AppDetect::isPsp() {
    return state == 1;
}

bool AppDetect::isDreamcast() {
    return state == 2;
}

bool AppDetect::isMenu() {
    return state == 3;
}

bool AppDetect::isGenericEmulator() {
    return state == 4;
}

void AppDetect::updateState(const std::string &lineInput) {
    
    //std::cout << "UPDATESTATE:" << lineInput << std::endl;
    
    std::size_t psp = lineInput.find("Added shared lib /data/lib/libppsspp_jni.so");
    std::size_t pspRx = lineInput.find("PPSSPP  : NativeApp.init() -- end");
    std::size_t reicast = lineInput.find("gdrom: Opened image");
    std::size_t mooreChipPlayer = lineInput.find("START u0 {cmp=com.moorechip.gameplayer");
    std::size_t retroStationPlayer = lineInput.find("START u0 {cmp=com.retrostation.gameplayer");
    std::size_t rxRetroArch = lineInput.find("cmp=com.retroarch/.MainMenuActivity");
    std::size_t rxMame = lineInput.find("for activity com.seleuco.mame4droid/.MAME4droid");
    std::size_t mooreChipMenu = lineInput.find("resumeClassName is com.moorechip.gamemenu");
    std::size_t rxMenu = lineInput.find("System.exit called, status: 0");
    std::size_t retroStationMenu = lineInput.find("resumeClassName is com.retrostation.gamemenu");

    
    if (psp != std::string::npos || pspRx != std::string::npos) {
        std::cout << "emulator: Detected PSP" << std::endl;
        state = 1;
        return;
    }
    if (reicast != std::string::npos) {
        std::cout << "emulator: Detected Dreamcast" << std::endl;
        state = 2;
        return;
    }
    if (mooreChipMenu != std::string::npos || retroStationMenu != std::string::npos || rxMenu != std::string::npos) {
        std::cout << "emulator: Detected Menu" << std::endl;
        state = 3;
        return;
    }
    if (mooreChipPlayer != std::string::npos || retroStationPlayer != std::string::npos || rxRetroArch != std::string::npos || rxMame != std::string::npos) {
        std::cout << "emulator: Detected Generic" << std::endl;
        state = 4;
        return;
    }
    state = 0;
}

int AppDetect::getType() {
    return state;
}
