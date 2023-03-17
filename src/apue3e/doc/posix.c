/*
 * 一般只考虑linux 和 mac os
 *
 * C标准头文件      linux都支持，mac os不支持 tgmath.h
 *
 * POSIX标准必须头文件  linux都支持，mac os不支持 wordexp.h
 *
 * POSIX标准XSI扩展头文件   linux不支持ndbm.h， mac os不支持cpio.h fmtmsg.h ftw.h utmpx.h sys/msg.h sys/statvfs.h
 *
 * POSIX标准可选头文件      linux不支持 mqueue.h trace.h，mac os不支持mqueue.h spawn.h stropts.h trace.h
 */


// 统一标准头文件
#include <unistd.h>
#include <stdio.h>

int main(){
    long val = sysconf(_SC_PAGE_SIZE);
    printf("%ld\n", val);
    return 0;

}
