#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main(){

    int fd = open("/home/shenyifei/c-workspace/apue3e/doc/file.c", O_RDONLY);
    if (fd < 0){
        printf("error");
        return 1;
    }
    char* buf[4096];
    read(fd, buf, 4096);
    printf("%s\n", buf);
    close(fd);
    return 0;
}
