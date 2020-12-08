#include "ResolutionSwitcher.h"
#include "Process.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include "Fs.h"

void ResolutionSwitcher::switchTo16by9() {
	std::cout << "resswitch: Switching to 16:9" << std::endl;
	std::string sixteenNine = "echo " + environment.get169Ratio()
			+ " > /sys/class/graphics/fb0/window_axis";
	system(sixteenNine.c_str());
	currentResolution = 9;
}

void ResolutionSwitcher::switchTo3by4() {
    std::cout << "resswitch: Switching to 3:4" << std::endl;
    std::string threeFour = "echo " + environment.get34Ratio()
                            + " > /sys/class/graphics/fb0/window_axis";
    system(threeFour.c_str());
    currentResolution = 3;
}

void ResolutionSwitcher::switchTo4by3() {
	std::cout << "resswitch: Switching to 4:3" << std::endl;
	std::string fourThree = "echo " + environment.get43Ratio()
			+ " > /sys/class/graphics/fb0/window_axis";
	system(fourThree.c_str());
	currentResolution = 4;
}

int ResolutionSwitcher::getCurrentResolution() const {
	return currentResolution;
}

void ResolutionSwitcher::toggleResolution() {
	if (getCurrentResolution() == 9) {
		switchTo4by3();
	} else if (getCurrentResolution() == 4) {
		switchTo3by4();
	} else {
	    switchTo16by9();
	}
}



void ResolutionSwitcher::revertColours() {
    screenSettings.setSaturationHue("0x1000000");
    screenSettings.setContrast(0);
    screenSettings.setBrightness(0);
    std::cout << "Reverting colours" << std::endl;
}

void ResolutionSwitcher::setScanlineColours() {
    screenSettings.setSaturationHue("0x1200000");
    screenSettings.setContrast(20);
    screenSettings.setBrightness(0);
    std::cout << "Setting scanline colours" << std::endl;
}

void ResolutionSwitcher::setNonScanlineColours() {
    screenSettings.setSaturationHue("0x1000000");
    screenSettings.setContrast(10);
    screenSettings.setBrightness(-5);
    std::cout << "Setting non scanline colours" << std::endl;
}

int ResolutionSwitcher::getCurrentRenderingMode() {
    std::string path;
    std::string currentMode;
    if (environment.isRetrostationFirmware()) {
        path = "/data/data/com.retrostation.platformdataprovider/shared_prefs/config.xml";
    } else {
        path = "/data/data/com.moorechip.platformdataprovider/shared_prefs/config.xml";
    }
    if (Fs::exists(path)) {
        process.exec("grep 6A8 " + path + R"( | cut -d ">" -f 2 | cut -d "<" -f 1 > /cache/rendermode)");
        std::ifstream rendermode("/cache/rendermode");
        if (rendermode.is_open()) {
            getline(rendermode, currentMode);
        }
    } {
        currentMode = "0";
    }
    std::cout << "Current mode is: "+currentMode << std::endl;
    return std::stoi(currentMode);
}
