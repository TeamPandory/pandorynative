#include "Android.h"
#include <string>

void Android::startActivity(const std::string& packageName, const std::string& activityName) {
    std::string activityString = "am start -n " + packageName + "/" + activityName;
    system(activityString.c_str());
}

void Android::safeShutdown() {
    system("input keyevent 26");
}

void Android::inputText(const std::string &text) {
    std::string cmd = "input text \"" + text + "\"";
    system(cmd.c_str());
}
