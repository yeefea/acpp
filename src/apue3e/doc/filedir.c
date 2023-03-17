/* #include "apue.h" */
#include <sys/stat.h>
#include <stdio.h>
int main(){
    struct stat buf;
    stat("filedir.c", &buf);
    printf("%d", buf.st_mode);

}
