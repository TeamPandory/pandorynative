#ifndef PANDORYKEY_PANDORACONTROLLER_H
#define PANDORYKEY_PANDORACONTROLLER_H
#include <string>
#include "Environment.h"

struct pandoraPlayer {
    bool start;
    bool coin;
    bool A;
    bool B;
    bool C;
    bool D;
    bool E;
    bool F;
};

class PandoraController {
protected:
    Environment environment;
    pandoraPlayer p1;
    pandoraPlayer p2;
public:
    void updateState(const std::string &lineInput);

    [[nodiscard]] const pandoraPlayer &getP1() const;

    [[nodiscard]] const pandoraPlayer &getP2() const;
};


#endif //PANDORYKEY_PANDORACONTROLLER_H
