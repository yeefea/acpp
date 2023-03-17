#include "apue.h"
#include <sys/wait.h>

int main(){
    char buf[MAXLINE];
    pid_t pid;
    int status;
    pid = getpid();
    printf("parent pid = %d\n", pid);
    pid = fork();
    if (pid < 0){
        printf("error");
        return 0;
    }
    if (pid == 0){
        printf("in child process pid=%d\n", getpid());
        return 0;
    }
    printf("in parent process\n");
    pid = waitpid(pid, &status, 0);
    return 0 ;
}
