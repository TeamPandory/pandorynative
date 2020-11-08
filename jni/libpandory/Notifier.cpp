#include "Notifier.h"

bool Notifier::notify(const std::string &message) {
    if (environment.isTrimUiFirmware()) {
        process.exec("am broadcast -a com.trimui.RX_UPDATE_INFO --es info \""+message+"\"");
    }
    return false;
}
