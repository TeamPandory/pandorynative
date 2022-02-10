#include <iostream>
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
    process.exec("rm -f /data/system/users/0/package-restrictions.xml");
    if (environment.isRetrostationFirmware()) {
        Fs::copy("pandory/package-restrictions-retrostation.xml", "/data/system/users/0/package-restrictions.xml");
    } else {
        Fs::copy("pandory/package-restrictions-moorechip.xml", "/data/system/users/0/package-restrictions.xml");
    }

    // copy updated savestate config
    Fs::copy("pandory/batch_update_game_support_features.txt", "/storage/external_storage/sdcard1/games/batch_update_game_support_features.txt");
    Fs::copy("pandory/batch_update_game_support_features.txt", "/storage/external_storage/sda1/games/batch_update_game_support_features.txt");
    Fs::copy("pandory/batch_update_game_support_features.txt", "/data/edata/games/batch_update_game_support_features.txt");
    process.exec("chmod 777 /data/edata/games/batch_update_game_support_features.txt");

    // Enable Dreamcast Saving!
    Fs::copy("pandory/dc.tgz", "/cache/dc.tgz");
    process.exec("mkdir -p /data/pandorydata/dc/");
    process.exec("busybox-armv7l tar xvf /cache/dc.tgz -C /data/pandorydata/dc/");
    process.exec("rm -f /cache/dc.tgz");

    // Enable Web Interface!!1
    Fs::copy("pandory/pandoryweb.tgz", "/cache/pandoryweb.tgz");
    process.exec("mkdir -p /data/pandorydata/www/");
    process.exec("busybox-armv7l tar xvf /cache/pandoryweb.tgz -C /data/pandorydata/www/");
    process.exec("chmod -R 777 /data/pandorydata/www");
    process.exec("rm -f /cache/pandoryweb.tgz");

    // Fix playstation bios .. and tekken!
    if (environment.isRetrostationFirmware()) {
        // blindly copy bios to the correct folder
        Fs::makeDirectory("/storage/external_storage/sdcard1/games/data/common/family/");
        Fs::makeDirectory("/storage/external_storage/sda1/games/data/common/family/");
        Fs::copy("/storage/external_storage/sdcard1/games/data/family/tk3/scph5501.bin", "/storage/external_storage/sdcard1/games/data/common/family/scph5501.bin");
        Fs::copy("/storage/external_storage/sda1/games/data/family/tk3/scph5501.bin", "/storage/external_storage/sda1/games/data/common/family/scph5501.bin");

        Fs::move("/storage/external_storage/sdcard1/games/data/family/tk/5004599.ccd", "/storage/external_storage/sdcard1/games/data/family/tk/tk.ccd");
        Fs::move("/storage/external_storage/sdcard1/games/data/family/tk/5004599.img", "/storage/external_storage/sdcard1/games/data/family/tk/tk.img");
        Fs::move("/storage/external_storage/sdcard1/games/data/family/tk/5004599.sub", "/storage/external_storage/sdcard1/games/data/family/tk/tk.sub");
        Fs::move("/storage/external_storage/sda1/games/data/family/tk/5004599.ccd", "/storage/external_storage/sda1/games/data/family/tk/tk.ccd");
        Fs::move("/storage/external_storage/sda1/games/data/family/tk/5004599.img", "/storage/external_storage/sda1/games/data/family/tk/tk.img");
        Fs::move("/storage/external_storage/sda1/games/data/family/tk/5004599.sub", "/storage/external_storage/sda1/games/data/family/tk/tk.sub");
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

        if (Fs::exists("/storage/external_storage/sdcard1")) {
            process.exec("mkdir -p /storage/external_storage/sdcard1/skin/backup");
            process.exec("mv /storage/external_storage/sdcard1/skin/*.png /data/media/0/skin/backup/");
            Fs::copy("pandory/skin/background.png", "/storage/external_storage/sdcard1/skin/background.png");
            Fs::copy("pandory/skin/loading.png", "/storage/external_storage/sdcard1/skin/loading.png");
            Fs::copy("pandory/skin/logo.png", "/storage/external_storage/sdcard1/skin/logo.png");
            process.exec("chmod -R 777 /storage/external_storage/sdcard1/skin/");
        }

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
    androidFilesystem.setOwner("/system/bin/dig", "root:shell");
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