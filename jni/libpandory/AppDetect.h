#ifndef PANDORYKEY_EMULATOR_H
#define PANDORYKEY_EMULATOR_H
#include <string>

class AppDetect {
protected:
    int state;

public:
    void updateState(const std::string& lineInput);
    bool isPsp();
    bool isDreamcast();
    bool isMenu();
    bool isGenericEmulator();
    int getType();
};


#endif //PANDORYKEY_EMULATOR_H
