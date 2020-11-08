#include "ScreenSettings.h"

void ScreenSettings::setSaturationHue(const std::string& saturation) {
    process.exec("echo \"" + saturation + "\" > /sys/class/video/vpp_saturation_hue");
}

void ScreenSettings::setBrightness(int brightness) {
    process.exec("echo "+std::to_string(brightness)+" > /sys/class/video/vpp_brightness");
}

void ScreenSettings::setContrast(int contrast) {
    process.exec("echo "+ std::to_string(contrast) +" > /sys/class/video/vpp_contrast");
}
