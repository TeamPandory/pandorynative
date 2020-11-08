#ifndef PANDORYKEY_ANDROID_H
#define PANDORYKEY_ANDROID_H
#include <string>


class Android {
public:
    void startActivity(const std::string& packageName, const std::string& activityName);
    void safeShutdown();
    void inputText(const std::string& text);
};


#endif //PANDORYKEY_ANDROID_H
