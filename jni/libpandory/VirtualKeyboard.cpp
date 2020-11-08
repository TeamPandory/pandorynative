#include "VirtualKeyboard.h"
#include <fcntl.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>

VirtualKeyboard::VirtualKeyboard() {
}

void VirtualKeyboard::init() {
    std::cout << "vkey: virtual keyboard initialized" << std::endl;
    int returnCode;
    uInput = open("/dev/uinput", O_WRONLY | O_NDELAY);
    if (uInput) {
        struct uinput_user_dev userDev;
        memset(&userDev, 0, sizeof(userDev));
        strncpy(userDev.name, "PandoryTool VKBD", 20);
        userDev.id.version = 4;
        userDev.id.bustype = BUS_USB;
        ioctl(uInput, UI_SET_EVBIT, EV_KEY);
        for (int i = KEY_1; i < KEY_F12; i++) {
            ioctl(uInput, UI_SET_KEYBIT, i);
        }
        returnCode = write(uInput, &userDev, sizeof(userDev));
        returnCode = (ioctl(uInput, UI_DEV_CREATE));
    }
}

void VirtualKeyboard::mashKey(int keyCode) {
    struct input_event pandoryEvt;
    memset(&pandoryEvt, 0, sizeof(pandoryEvt));
    gettimeofday(&pandoryEvt.time, NULL);
    pandoryEvt.type = EV_KEY;
    pandoryEvt.code = keyCode;
    pandoryEvt.value = 1;
    write(uInput, &pandoryEvt, sizeof(pandoryEvt));

    memset(&pandoryEvt, 0, sizeof(pandoryEvt));
    gettimeofday(&pandoryEvt.time, NULL);
    pandoryEvt.type = EV_SYN;
    pandoryEvt.code = SYN_REPORT;
    pandoryEvt.value = 0;
    write(uInput, &pandoryEvt, sizeof(pandoryEvt));

    memset(&pandoryEvt, 0, sizeof(pandoryEvt));
    gettimeofday(&pandoryEvt.time, NULL);
    pandoryEvt.type = EV_KEY;
    pandoryEvt.code = keyCode;
    pandoryEvt.value = 0;
    write(uInput, &pandoryEvt, sizeof(pandoryEvt));

    memset(&pandoryEvt, 0, sizeof(pandoryEvt));
    gettimeofday(&pandoryEvt.time, NULL);
    pandoryEvt.type = EV_SYN;
    pandoryEvt.code = SYN_REPORT;
    pandoryEvt.value = 0;
    write(uInput, &pandoryEvt, sizeof(pandoryEvt));
}
