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

    if (Fs::exists("/data/pandorydata/dc/emu.cfg")) {
        fsMounter.bindMount("/data/pandorydata/dc/", "/system/vendor/games/dc/");
    }

    process.exec("sleep 20");
    shellEnabler.enableTelnet();
    shellEnabler.enableHTTP();

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
                if (!Fs::exists("/data/no-settings-switch")) {
                    if (environment.isRetrostationFirmware()) {
                        android.startActivity("com.retrostation.systemsetting",
                                              "com.retrostation.systemsetting.activity.main.SystemSettingActivity");
                    } else {
                        android.startActivity("com.moorechip.systemsetting",
                                              "com.moorechip.systemsetting.activity.SystemSettingActivity");
                    }
                }
            } else if (p1.coin) {
                if (Fs::exists("/data/coin-to-pause")) {
                    mooreChip.pause();
                }
            }
            else if (p1.start && p1.A && p1.B && p1.C) {
                if (!Fs::exists("/data/no-safe-shutdown")) {
                    android.safeShutdown();
                }
            } else if (p1.start && p1.D) {
                // mash F1 key
                if (!Fs::exists("/data/no-dipswitches")) {
                    for (int j = 0; j < 5; j++) {
                        virtualKeyboard.mashKey(VK_F1);
                    }
                }
            } else if (p1.start && p1.E) {
                // switch res
                if (jailbreak.isUltimate()) {
                    if (!Fs::exists("/data/no-aspect-toggle")) {
                        resolutionSwitcher.toggleResolution();
                    }
                }
            } else if (p1.start && p1.F) {
                if (!Fs::exists("/data/no-pause")) {
                    mooreChip.pause();
                }
            }

            std::size_t keyPause = lineInput.find("fpga2key key: 8, press: 1");
            std::size_t keyPauseReleased = lineInput.find("fpga2key key: 8, press: 0");
            if (keyPauseReleased != std::string::npos) {
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
                        if (!Fs::exists("/data/no-android-switch")) {
                            std::cout << "Launching" << std::endl;
                            if (mode == 0) {
                                android.startActivity("com.android.launcher",
                                                      "com.android.launcher2.Launcher");
                                mode = 1;
                            } else if (mode == 1) {
                                if (environment.isRetrostationFirmware()) {
                                    android.startActivity("com.retrostation.gamemenu",
                                                          "com.retrostation.gamemenu.activity.MenuActivity");
                                } else {
                                    android.startActivity("com.moorechip.gamemenu",
                                                          "com.moorechip.gamemenu.activity.MenuActivity");
                                }
                                mode = 0;
                                if (Fs::exists("/data/data/com.retroarch.ra32/lib/libretroarch-activity.so")) {
                                    mode = 2;
                                }
                            } else if (mode == 2) {
                                android.startActivity("com.retroarch.ra32",
                                                      "com.retroarch.browser.mainmenu.MainMenuActivity");
                                mode = 0;
                            }
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
