#ifndef PANDORYKEY_RESOLUTIONSWITCHER_H
#define PANDORYKEY_RESOLUTIONSWITCHER_H
#include <string>
#include "Environment.h"
#include "Process.h"
#include "ScreenSettings.h"
#include <iostream>

class ResolutionSwitcher
{
protected:
	Environment environment;
    Process process;
    ScreenSettings screenSettings;
    int currentResolution = 9;

public:
    void switchTo16by9();
    void switchTo4by3();
    void switchTo3by4();
    [[nodiscard]] int getCurrentResolution() const;
    void toggleResolution();
    void revertColours();
    void setNonScanlineColours();
    void setScanlineColours();
    int getCurrentRenderingMode();

};


#endif //PANDORYKEY_RESOLUTIONSWITCHER_H
