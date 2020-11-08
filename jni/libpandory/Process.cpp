#include "Process.h"

bool Process::kill(int processId) {
    std::string cmd = "kill " + std::to_string(processId);
    system(cmd.c_str());
    return false;
}

bool Process::killAll(const std::string &process) {
    std::string cmd = "killall " + process;
    system(cmd.c_str());
    return false;
}

bool Process::exec(const std::string &path) {
    system(path.c_str());
    return false;
}
