#ifndef PANDORYKEY_VIRTUALKEYBOARD_H
#define PANDORYKEY_VIRTUALKEYBOARD_H
#include <linux/uinput.h>

static const int VK_F1 = KEY_F1;

class VirtualKeyboard {
protected:
    int uInput;
public:
    VirtualKeyboard();
    void mashKey(int keyCode);
    void init();
};


#endif //PANDORYKEY_VIRTUALKEYBOARD_H
