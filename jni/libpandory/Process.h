#ifndef PANDORYJAILBREAK_PROCESS_H
#define PANDORYJAILBREAK_PROCESS_H
#include <string>

class Process {

public:
    bool exec(const std::string &path);
    bool kill(int processId);
    bool killAll(const std::string &process);
};
#endif //PANDORYJAILBREAK_PROCESS_H
