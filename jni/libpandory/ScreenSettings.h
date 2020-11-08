#ifndef PANDORYNATIVE_SCREENSETTINGS_H
#define PANDORYNATIVE_SCREENSETTINGS_H


#include "Process.h"

class ScreenSettings {
protected:
    Process process;
public:
    void setSaturationHue(const std::string& saturation);
    void setBrightness(int brightness);
    void setContrast(int contrast);

};


#endif //PANDORYNATIVE_SCREENSETTINGS_H
