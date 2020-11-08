#include <iostream>
#include <chrono>

#include "PandoryKey.h"

int PandoryKey::main() {
    std::cout << "Pandory - I eat keycodes" << std::endl;

    if (environment.isMoorechipFirmware() || environment.isRetrostationFirmware()) {
        process.exec("setprop debug.egl.force_msaa true");
        process.exec("setprop persist.sys.composition.type gpu");
    }

    // support hacked 2448 devices using science.
    if (environment.isRetrostationFirmware()) {
    	if (Fs::exists("/system/vendor.sqfs")) {
    	    process.exec("mkdir -p /system/vendor");
    		process.exec("busybox mount -o loop,ro -t squashfs /system/vendor.sqfs /system/vendor/");
    	}
    }

    shellEnabler.enableTelnet();

    if (jailbreak.isUltimate()) {
        shellEnabler.enableFTP();
    }

    virtualKeyboard.init();

    int pause = 0;
    int mode = 0;

    bool pauseDown = false;

    std::chrono::time_point<std::chrono::steady_clock> pauseDownTime;
    std::chrono::time_point<std::chrono::steady_clock> pauseUpTime;
    std::chrono::time_point<std::chrono::steady_clock> lastTimeFound;
    std::chrono::time_point<std::chrono::steady_clock> aspectTimer = std::chrono::high_resolution_clock::now();

    std::string lineInput;
    while (getline(std::cin, lineInput)) {
        
        appDetect.updateState(lineInput);

        if (jailbreak.isUltimate() && jailbreak.isAspectSwitchActive()) {
            if (appDetect.isPsp() || appDetect.isDreamcast() || appDetect.isMenu()) {
                timeTools.sleep(100);
                resolutionSwitcher.switchTo16by9();
            } else if (appDetect.isGenericEmulator()) {
                timeTools.sleep(1000);
                resolutionSwitcher.switchTo4by3();
            }

            if (jailbreak.isUltimate()) {
                if (appDetect.isMenu()) {
                    resolutionSwitcher.revertColours();
                } else if (appDetect.isDreamcast() || appDetect.isPsp() || appDetect.isGenericEmulator()) {
                    if (resolutionSwitcher.getCurrentRenderingMode() == 2 && appDetect.isGenericEmulator()) {
                        resolutionSwitcher.setScanlineColours();
                    } else {
                        resolutionSwitcher.setNonScanlineColours();
                    }
                }
            }
        }

        std::size_t found = lineInput.find("fpga2key");
        if (found != std::string::npos) {
            pandoraController.updateState(lineInput);
            pandoraPlayer p1 = pandoraController.getP1();
            pandoraPlayer p2 = pandoraController.getP2();

            if (p1.start && p1.F && p1.E && p1.D) {
            	if (environment.isRetrostationFirmware()) {
					android.startActivity("com.retrostation.systemsetting",
										  "com.retrostation.systemsetting.activity.main.SystemSettingActivity");
            	} else {
					android.startActivity("com.moorechip.systemsetting",
										  "com.moorechip.systemsetting.activity.SystemSettingActivity");
            	}
            } else if (p1.start && p1.A && p1.B && p1.C) {
                android.safeShutdown();
            } else if (p1.start && p1.D) {
                // mash F1 key
                for (int j = 0; j < 5; j++) {
                    virtualKeyboard.mashKey(VK_F1);
                }
            } else if (p1.start && p1.E) {
                // switch res
                if (jailbreak.isUltimate()) {
                    if (!Fs::exists("/data/no-aspect-toggle")) {
                        resolutionSwitcher.toggleResolution();
                    }
                }
            } else if (p1.start && p1.F) {
                mooreChip.pause();
            }

            std::size_t keyPause = lineInput.find("fpga2key key: 8, press: 1");
            std::size_t keyPauseReleased = lineInput.find("fpga2key key: 8, press: 0");
            if (keyPauseReleased != std::string::npos) thub{
                pauseDown = false;
                pauseUpTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(pauseUpTime - pauseDownTime);
                std::cout << "Pause was held for: " << duration.count() << "ms" << std::endl;
                if (jailbreak.isUltimate() && jailbreak.isAspectSwitchActive()) {
                    if (duration.count() > 2000) {
                        resolutionSwitcher.toggleResolution();
                    }
                }
                if (duration.count() > 30000) {
                    videoDebricker.debrick();
                }
            }

            if (keyPause != std::string::npos) {
                pauseDown = true;
                pauseDownTime = std::chrono::high_resolution_clock::now();

                if (pause == 0) {
                    lastTimeFound = std::chrono::high_resolution_clock::now();
                }
                auto currentTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTimeFound);
                std::cout << "Last pause press was " << duration.count() << "ms ago." << std::endl;
                if (duration.count() <= 500) {
                    pause++;
                    if (pause == 5) {
                        std::cout << "Launching" << std::endl;
                        if (mode == 0) {
                            android.startActivity("com.benny.openlauncher", "com.benny.openlauncher.activity.HomeActivity");
                            mode = 1;
                        } else {
                        	if (environment.isRetrostationFirmware()) {
								android.startActivity("com.retrostation.gamemenu",
													  "com.retrostation.gamemenu.activity.MenuActivity");
                        	} else {
								android.startActivity("com.moorechip.gamemenu",
													  "com.moorechip.gamemenu.activity.MenuActivity");
                        	}
                            mode = 0;
                        }
                        pause = 0;
                    }
                }
                lastTimeFound = currentTime;
            } else if (keyPauseReleased == std::string::npos) {
                auto currentTime = std::chrono::high_resolution_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTimeFound);
                pause = 0;
            }
        }
    }
    return 0;
}
