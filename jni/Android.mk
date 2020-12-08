LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE := pandoryjailbreak
LOCAL_LDLIBS := -llog -lm
LOCAL_CFLAGS := -O3 -UNDEBUG
LOCAL_CPPFLAGS := -std=c++17 -s
LOCAL_CPP_FEATURES += exceptions
LOCAL_SRC_FILES :=  jailbreak/src/main.cpp \
                    jailbreak/src/PandoryJailbreak.cpp \
                    jailbreak/src/Jailbreak/JailbreakAbstract.cpp \
                    jailbreak/src/Jailbreak/MoorechipJailbreak.cpp \
                    jailbreak/src/Jailbreak/TrimuiJailbreak.cpp \
                    libpandory/AndroidFilesystem.cpp \
                    libpandory/Fs.cpp \
                    libpandory/DD.cpp \
                    libpandory/TimeTools.cpp \
                    libpandory/FsMounter.cpp \
                    libpandory/Environment.cpp \
                    libpandory/Notifier.cpp \
                    libpandory/Process.cpp
include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)
LOCAL_MODULE := pandorykey
LOCAL_LDLIBS := -llog -lm
LOCAL_CFLAGS := -O3 -UNDEBUG
LOCAL_CPPFLAGS := -std=c++17 -s
LOCAL_CPP_FEATURES += exceptions
LOCAL_SRC_FILES :=  pandorykey/src/main.cpp \
                    pandorykey/src/PandoryKey.cpp \
                    libpandory/VirtualKeyboard.cpp \
                    libpandory/Environment.cpp \
                    libpandory/Fs.cpp \
                    libpandory/ScreenSettings.cpp \
                    libpandory/TimeTools.cpp \
                    libpandory/ResolutionSwitcher.cpp \
                    libpandory/PandoraController.cpp \
                    libpandory/Android.cpp \
                    libpandory/FsMounter.cpp \
                    libpandory/VideoDebricker.cpp \
                    libpandory/Process.cpp \
                    libpandory/ShellEnabler.cpp \
                    libpandory/AppDetect.cpp \
                    libpandory/MooreChip.cpp \
                    libpandory/Jailbreak.cpp
include $(BUILD_EXECUTABLE)

