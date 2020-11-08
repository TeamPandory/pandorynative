#include <cstdlib>
#include "DD.h"

bool DD::copy(const std::string &src, const std::string &dest) {
//    busybox dd if=/dev/block/mtdblock0 of=/data/mtdblock0.img
  //  busybox dd if=/dev/block/mtdblock1 of=/data/mtdblock1.img
  std::string cmd = "busybox dd if="+src+" of="+dest;
  system(cmd.c_str());
  return false;
}
