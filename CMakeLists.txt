cmake_minimum_required(VERSION 3.16)
project(PandoryNative)

set(CMAKE_CXX_STANDARD 14)

include_directories(jni/jailbreak/src)
include_directories(jni/jailbreak/src/Jailbreak)
include_directories(jni/libpandory)
include_directories(jni/pandorykey/src)

add_executable(PandoryNative
        jni/jailbreak/src/Jailbreak/JailbreakAbstract.cpp
        jni/jailbreak/src/Jailbreak/JailbreakAbstract.h
        jni/jailbreak/src/Jailbreak/MoorechipJailbreak.cpp
        jni/jailbreak/src/Jailbreak/MoorechipJailbreak.h
        jni/jailbreak/src/Jailbreak/TrimuiJailbreak.cpp
        jni/jailbreak/src/Jailbreak/TrimuiJailbreak.h
        jni/jailbreak/src/main.cpp
        jni/jailbreak/src/PandoryJailbreak.cpp
        jni/jailbreak/src/PandoryJailbreak.h
        jni/libpandory/Android.cpp
        jni/libpandory/Android.h
        jni/libpandory/AndroidFilesystem.cpp
        jni/libpandory/AndroidFilesystem.h
        jni/libpandory/AndroidProperties.cpp
        jni/libpandory/AndroidProperties.h
        jni/libpandory/AppDetect.cpp
        jni/libpandory/AppDetect.h
        jni/libpandory/DD.cpp
        jni/libpandory/DD.h
        jni/libpandory/Environment.cpp
        jni/libpandory/Environment.h
        jni/libpandory/Fs.cpp
        jni/libpandory/Fs.h
        jni/libpandory/FsMounter.cpp
        jni/libpandory/FsMounter.h
        jni/libpandory/Jailbreak.cpp
        jni/libpandory/Jailbreak.h
        jni/libpandory/MooreChip.cpp
        jni/libpandory/MooreChip.h
        jni/libpandory/Notifier.cpp
        jni/libpandory/Notifier.h
        jni/libpandory/PandoraController.cpp
        jni/libpandory/PandoraController.h
        jni/libpandory/Process.cpp
        jni/libpandory/Process.h
        jni/libpandory/ResolutionSwitcher.cpp
        jni/libpandory/ResolutionSwitcher.h
        jni/libpandory/ShellEnabler.cpp
        jni/libpandory/ShellEnabler.h
        jni/libpandory/TimeTools.cpp
        jni/libpandory/TimeTools.h
        jni/libpandory/VideoDebricker.cpp
        jni/libpandory/VideoDebricker.h
        jni/libpandory/VirtualKeyboard.cpp
        jni/libpandory/VirtualKeyboard.h
        jni/pandorykey/src/main.cpp
        jni/pandorykey/src/PandoryKey.cpp
        jni/pandorykey/src/PandoryKey.h
        PandoryNative.cpp jni/libpandory/ScreenSettings.cpp jni/libpandory/ScreenSettings.h)
