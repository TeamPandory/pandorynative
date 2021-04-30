/*
 * ShellEnabler.cpp
 *
 *  Created on: Aug 27, 2020
 *      Author: dajoho
 */

#include <string>
#include "ShellEnabler.h"
#include "Process.h"

ShellEnabler::ShellEnabler() {
}

void ShellEnabler::enableTelnet() {
    //process.exec("ifconfig usbnet0 dhcp");
    process.exec("ip link set usbnet0 up");
    process.exec("netcfg usbnet0 dhcp");
    process.exec("netcfg usbnet0 up");
    process.exec("setprop net.dns1 1.1.1.1");
    process.exec("setprop net.dns2 1.0.0.1");
    process.exec("setprop net.usbnet0.dns1 1.1.1.1");
    process.exec("setprop net.usbnet0.dns2 1.0.0.1");
    process.exec("netcfg ip6tnl0 up");
    process.exec("netcfg tunl0 up");
    process.exec("netcfg sit0 up");
    process.exec("ndc resolver setifdns netusb0 "" 1.1.1.1 1.0.0.1");
    process.exec("ndc resolver setdefaultif netusb0");
    process.exec("busybox-armv7l telnetd -p 4444 -l ash");
}

void ShellEnabler::enableFTP() {
	process.exec("busybox-armv7l tcpsvd -vE 0.0.0.0 7777 ftpd -wA / &");
}

void ShellEnabler::enableHTTP() {
    process.exec("busybox-armv7l httpd -p 0.0.0.0:80 -h /data/pandorydata/www &");
}

ShellEnabler::~ShellEnabler() {
}