#include "MoorechipJailbreak.h"
#include "../../../libpandory/Fs.h"
#include "JailbreakAbstract.h"

bool MoorechipJailbreak::mountFilesystem()
{
	androidFilesystem.remountSystemReadWrite();
    return true;
}

bool MoorechipJailbreak::copyFiles()
{
    JailbreakAbstract::copyFiles();

    Fs::copy("pandory/pandorykey", "/system/bin/pandorykey");
    Fs::copy("pandory/dig", "/system/bin/dig");
    Fs::copy("pandory/meta.bin", "/data/meta.bin");
    Fs::copy("pandory/res.bin", "/data/res.bin");
    Fs::copy("pandory/pandory.sh", "/system/bin/pandory.sh");
    if (environment.isRetrostationFirmware()) {
        Fs::copy("pandory/package-restrictions-retrostation.xml", "/data/system/users/0/package-restrictions.xml");
    } else {
        Fs::copy("pandory/package-restrictions-moorechip.xml", "/data/system/users/0/package-restrictions.xml");
    }
    process.exec("chown system:system /data/system/users/0/package-restrictions.xml");

    if (!Fs::exists("/data/mtdblock0.img")) {
        dd.copy("/dev/block/mtdblock0", "/data/mtdblock0.img");
    }
    if (!Fs::exists("/data/mtdblock1.img")) {
        dd.copy("/dev/block/mtdblock1", "/data/mtdblock1.img");
    }
    
    return true;
}

bool MoorechipJailbreak::copyBranding()
{
    if (environment.isRetrostationFirmware()) {
        Fs::makeDirectory("/data/config/skin");
        Fs::copy("pandory/skin/background.png", "/data/config/skin/background.png");
        Fs::copy("pandory/skin/loading.png", "/data/config/skin/loading.png");
        Fs::copy("pandory/skin/logo.png", "/data/config/skin/logo.png");
        process.exec("chmod -R 777 /data/config/skin/");
    } else if (environment.isMoorechipFirmware()) {
        Fs::makeDirectory("/sdcard/skin");
        Fs::copy("pandory/skin/background.png", "/sdcard/skin/background.png");
        Fs::copy("pandory/skin/loading.png", "/sdcard/skin/loading.png");
        Fs::copy("pandory/skin/logo.png", "/sdcard/skin/logo.png");
        process.exec("chmod -R 777 /data/edata/skin/");

        if (Fs::exists("/data/edata")) {
            Fs::makeDirectory("/data/edata/skin");
            Fs::copy("pandory/skin/background.png", "/data/edata/skin/background.png");
            Fs::copy("pandory/skin/loading.png", "/data/edata/skin/loading.png");
            Fs::copy("pandory/skin/logo.png", "/data/edata/skin/logo.png");
            process.exec("chmod -R 777 /data/edata/skin/");

        }
    }
    JailbreakAbstract::copyBranding();
    return true;
}

bool MoorechipJailbreak::setPermissions()
{
    androidFilesystem.setPermissions("/system/app/DataStatistics.apk", 400);
    androidFilesystem.setPermissions("/system/bin/dig", 755);
    androidFilesystem.setPermissions("/system/bin/pandory.sh", 755);
    androidFilesystem.setPermissions("/system/bin/pandorykey", 755);
    androidFilesystem.setPermissions("/system/bin/adb", 755);
    androidFilesystem.setOwner("/system/bin/dig", "root:shell");
    androidFilesystem.setOwner("/system/bin/adb", "root:shell");
    androidFilesystem.setOwner("/system/bin/pandory.sh", "root:shell");
    androidFilesystem.setOwner("/system/bin/pandorykey", "root:shell");
    JailbreakAbstract::setPermissions();
    return true;
}

bool MoorechipJailbreak::finish()
{
    process.exec("settings put global install_non_market_apps 1");
    process.exec("mv ../OTA ../OTA.done");
    JailbreakAbstract::finish();
    return true;
}