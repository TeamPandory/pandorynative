#include "TimeTools.h"
#include <chrono>
#include <thread>

void TimeTools::sleep(int milliseconds) {
    std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
}
