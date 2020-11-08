#ifndef PANDORYJAILBREAK_FSMOUNTER_H
#define PANDORYJAILBREAK_FSMOUNTER_H

#include <string>
#include "Process.h"

class FsMounter {
protected:
    Process process;

public:
    bool mount(const std::string &device, const std::string &mountPoint);
    bool unmount(const std::string &device);
};

#endif //PANDORYJAILBREAK_FSMOUNTER_H
