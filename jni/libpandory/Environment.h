#ifndef PANDORYJAILBREAK_ENVIRONMENT_H
#define PANDORYJAILBREAK_ENVIRONMENT_H
#include <string>

class Environment {

public:
	std::string get34Ratio();
    std::string get43Ratio();
	std::string get169Ratio();
    bool isMoorechipFirmware();
    bool isRetrostationFirmware();
    bool isTrimUiFirmware();
};


#endif //PANDORYJAILBREAK_ENVIRONMENT_H
