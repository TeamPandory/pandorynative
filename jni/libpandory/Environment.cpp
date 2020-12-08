#include "Environment.h"
#include "Fs.h"

bool Environment::isMoorechipFirmware() {
    return Fs::exists("/system/app/GamePlayer.apk");
}

bool Environment::isTrimUiFirmware() {
    return Fs::exists("/system/priv-app/RxMAME4droid/MAME4droid.apk");
}

bool Environment::isRetrostationFirmware() {
	return Fs::exists("/data/data/com.retrostation.gameplayer/shared_prefs/multidex.version.xml");
}

std::string Environment::get34Ratio() {
    return std::string(isTrimUiFirmware() ? "0 0 1919 1079" : "370 0 909 719");
}

std::string Environment::get43Ratio() {
	if (isTrimUiFirmware()) {
		return std::string("240 0 1679 1079");
	}
	return std::string("160 0 1119 719");
}

std::string Environment::get169Ratio() {
	if (isTrimUiFirmware()) {
		return std::string("0 0 1919 1079");
	}
	return std::string("0 0 1279 719");
}
