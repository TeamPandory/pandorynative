#ifndef PANDORYJAILBREAK_ANDROIDPROPERTIES_H
#define PANDORYJAILBREAK_ANDROIDPROPERTIES_H

#include <string>
#include "Process.h"

class AndroidProperties {
protected:
    Process process;

public:
    bool setProperty(const std::string &propertyName, const std::string &propertyValue);
};

#endif //PANDORYJAILBREAK_ANDROIDPROPERTIES_H
