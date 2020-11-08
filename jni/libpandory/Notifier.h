#ifndef PANDORYJAILBREAK_NOTIFIER_H
#define PANDORYJAILBREAK_NOTIFIER_H

#include <string>
#include "Environment.h"
#include "Process.h"

class Notifier {
protected:
    Environment environment;
    Process process;
public:
    bool notify(const std::string &message);
};
#endif //PANDORYJAILBREAK_NOTIFIER_H
