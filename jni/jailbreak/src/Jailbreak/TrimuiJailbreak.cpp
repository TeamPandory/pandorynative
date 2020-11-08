#include "TrimuiJailbreak.h"
#include <iostream>
#include "../../../libpandory/Fs.h"
#include "JailbreakAbstract.h"

bool TrimuiJailbreak::notify(const std::string& msg)
{
    notifier.notify(msg);
    return true;
}

bool TrimuiJailbreak::init()
{
    notify("Pandory Jailbreak - by emuchicken and dajoho");
    process.killAll("sh");
    timeTools.sleep(2000);
    notify("Installing. Please stand by...");
    process.exec("rm -rf /system/media/audio/*");
    process.exec("echo \"========= SYSTEM ==========\" > log.txt");
	process.exec("find /system >> log.txt");
	process.exec("echo \"========= DATA ==========\" >> log.txt");
	process.exec("find /data >> log.txt");
	process.exec("echo \"========= PARTITIONS ==========\" >> log.txt");
	process.exec("cat /proc/partitions >> log.txt");
	process.exec("echo \"========= DEVBLOCK ==========\" >> log.txt");
	process.exec("find /dev/block >> log.txt");
	process.exec("echo \"========= DF ==========\" >> log.txt");
	process.exec("df >> log.txt");
	process.exec("echo \"========= PS ==========\" >> log.txt");
	process.exec("ps >> log.txt");
	process.exec("busybox ps >> log.txt");
    return true;
}

bool TrimuiJailbreak::mountFilesystem()
{
    androidFilesystem.remountSystemReadWrite();
    return true;
}

bool TrimuiJailbreak::copyFiles()
{
	Fs::makeDirectory("/data/bin");
    Fs::copy("pandory/pandorykey", "/data/bin/pandorykey");
    // Surf on top of copyfiles.sh to start pandorykey at boot
    if (!Fs::exists("/data/pandory/copyfiles.sh")) {
        Fs::copy("/system/etc/copyfiles.sh", "/data/pandory/copyfiles.sh");
        Fs::copy("/system/etc/copyfiles.sh", "/system/etc/copyfiles2.sh");
    }
    Fs::copy("pandory/trimui/copyfiles.sh", "/system/etc/copyfiles.sh");

    // pixels!
    if (!Fs::exists("/data/pandory/retroarch.cfg")) {
        Fs::copy("/data/media/0/Android/data/com.retroarch/files/retroarch.cfg", "/data/pandory/retroarch.cfg");
        Fs::copy("/data/media/0/Android/data/com.retroarch/files/retroarch-core-options.cfg", "/data/pandory/retroarch-core-options.cfg");
    }
    Fs::copy("pandory/trimui/retroarch/retroarch.cfg", "/data/media/0/Android/data/com.retroarch/files/retroarch.cfg");
    Fs::copy("pandory/trimui/retroarch/retroarch-core-options.cfg", "/data/media/0/Android/data/com.retroarch/files/retroarch-core-options.cfg");
    
    if (!Fs::exists("/data/pandory/fbalist.txt")) {
        Fs::copy("/data/media/0/mame/fbalist.txt", "/data/pandory/fbalist.txt");
    }
    process.exec("cat /data/pandory/fbalist.txt > /data/media/0/mame/fbalist.txt");
    process.exec("cat pandory/trimui/fbalist.txt >> /data/media/0/mame/fbalist.txt");
    
    JailbreakAbstract::copyFiles();
    return true;
}

bool TrimuiJailbreak::copyBranding()
{
    if (!Fs::exists("/data/pandory/01.jpg")) {
        Fs::copy("/storage/emulated/0/fw/wallpaper/01.jpg", "/storage/emulated/0/fw/wallpaper/11.jpg");
        Fs::copy("/storage/emulated/0/fw/wallpaper/01.jpg", "/data/pandory/01.jpg");
        Fs::copy("/storage/emulated/0/fw/bgm.mp3", "/data/pandory/bgm.mp3");
    }
    Fs::copy("pandory/bgm.mp3", "/storage/emulated/0/fw/bgm.mp3");
    Fs::copy("pandory/skin/mai.jpg", "/storage/emulated/0/fw/wallpaper/01.jpg");
    Fs::copy("pandory/skin/supercoco.jpg", "/storage/emulated/0/fw/wallpaper/12.jpg");
    
    JailbreakAbstract::copyBranding();
    return true;
}

bool TrimuiJailbreak::setPermissions()
{
    androidFilesystem.setPermissions("/data/bin/pandorykey", 755);
    JailbreakAbstract::setPermissions();
    return true;
}

bool TrimuiJailbreak::finish()
{
    process.exec("mv rx_1898_update.sh rx_1898_update.sh.done");
    fsMounter.unmount("/sdcard");
    for (int i=5;i>0;i--) {
        notify("Finished! Rebooting in " + std::to_string(i) +" seconds...");
        timeTools.sleep(500); // not really seconds
    }
    JailbreakAbstract::finish();
    return true;
}
