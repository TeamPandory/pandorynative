#include "JailbreakAbstract.h"
#include "../../../libpandory/Fs.h"


bool JailbreakAbstract::init()
{
	process.killAll("pandorykey");
    process.killAll("dig");
    return true;
}

bool JailbreakAbstract::notify(const std::string& msg)
{
    return true;
}

bool JailbreakAbstract::copyFiles()
{
    process.exec("pm uninstall com.benny.openlauncher");
    process.exec("pm install -r pandory/Launcher2.apk");
    Fs::copy("pandory/busybox-armv7l", "/system/bin/busybox-armv7l");
    process.exec("ln -s /system/bin/busybox-armv7l /system/bin/ftpd");
    return true;
}


bool JailbreakAbstract::copyBranding()
{
    if (!Fs::exists("/data/pandory/bootvideo") && Fs::exists("/system/etc/bootvideo")) {
        Fs::copy("/system/etc/bootvideo", "/data/pandory/bootvideo");
    }
    process.exec("rm -f /system/etc/bootvideo");
    Fs::copy("pandory/bootvideo", "/system/etc/bootvideo");
    process.exec("touch /system/pandory_was_here");
    return true;
}

bool JailbreakAbstract::setPermissions()
{
    androidFilesystem.setPermissions("/system/bin/busybox-armv7l", 755);
    androidFilesystem.setOwner("/system/bin/busybox-armv7l", "root:shell");
    return true;
}

bool JailbreakAbstract::finish()
{
	process.exec("sync");
    process.exec("reboot");
    return true;
}


bool JailbreakAbstract::jailbreak()
{
    init();
    mountFilesystem();   
    Fs::makeDirectory("/data/pandory");
    copyFiles();
    copyBranding();
    setPermissions();
    finish();
    return true;
}
