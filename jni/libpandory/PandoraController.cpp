#include <string>
#include "PandoraController.h"



void PandoraController::updateState(const std::string &lineInput) {
	std::size_t p1APress = lineInput.find("fpga2key key: 49, press: 1");
	std::size_t p1ARelease = lineInput.find("fpga2key key: 49, press: 0");
	std::size_t p1BPress = lineInput.find("fpga2key key: 37, press: 1");
	std::size_t p1BRelease = lineInput.find("fpga2key key: 37, press: 0");
	std::size_t p1CPress = lineInput.find("fpga2key key: 38, press: 1");
	std::size_t p1CRelease = lineInput.find("fpga2key key: 38, press: 0");
	std::size_t p1DPress = lineInput.find("fpga2key key: 39, press: 1");
	std::size_t p1DRelease = lineInput.find("fpga2key key: 39, press: 0");
	std::size_t p1EPress = lineInput.find("fpga2key key: 43, press: 1");
	std::size_t p1ERelease = lineInput.find("fpga2key key: 43, press: 0");
	std::size_t p1FPress = lineInput.find("fpga2key key: 40, press: 1");
	std::size_t p1FRelease = lineInput.find("fpga2key key: 40, press: 0");
	std::size_t p1StartPress = lineInput.find("fpga2key key: 9, press: 1");
	std::size_t p1StartRelease = lineInput.find("fpga2key key: 9, press: 0");
    std::size_t p1CoinPress = lineInput.find("fpga2key key: 10, press: 1");
    std::size_t p1CoinRelease = lineInput.find("fpga2key key: 10, press: 0");
	std::size_t keyPause = lineInput.find("fpga2key key: 8, press: 1");
	std::size_t keyPauseReleased = lineInput.find("fpga2key key: 8, press: 0");

    if (p1APress != std::string::npos) p1.A = true;
    if (p1ARelease != std::string::npos) p1.A = false;
    if (p1BPress != std::string::npos) p1.B = true;
    if (p1BRelease != std::string::npos) p1.B = false;
    if (p1CPress != std::string::npos) p1.C = true;
    if (p1CRelease != std::string::npos) p1.C = false;
    if (p1DPress != std::string::npos) p1.D = true;
    if (p1DRelease != std::string::npos) p1.D = false;
    if (p1EPress != std::string::npos) p1.E = true;
    if (p1ERelease != std::string::npos) p1.E = false;
    if (p1FPress != std::string::npos) p1.F = true;
    if (p1FRelease != std::string::npos) p1.F = false;
    if (p1StartPress != std::string::npos) p1.start = true;
    if (p1StartRelease != std::string::npos) p1.start = false;
    if (p1CoinPress != std::string::npos) p1.coin = true;
    if (p1CoinRelease != std::string::npos) p1.coin = false;

    if (keyPause != std::string::npos) p2.coin = true;
    if (keyPauseReleased != std::string::npos) p2.coin = false;
}

const pandoraPlayer &PandoraController::getP1() const {
    return p1;
}

const pandoraPlayer &PandoraController::getP2() const {
    return p2;
}
