#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include "apue.h"
#define separator(s) printf(">>>>>>> %s <<<<<<\n", #s) 

/*
 * man
 * 1 可执行程序
 * 2 系统调用
 * 3 函数调用
 * 4 特殊文件 如/dev
 * 5 文件格式 如/etc/passwd
 * 6 游戏
 * 7 杂项
 * 8 系统管理员命令 root相关命令 mkfs
 * 9 内核routine
 *
 *
 */

/*
 * dirent.h 目录相关操作
 * opendir
 * readdir
 * closedir
 *
 *
 *
 */

void demo_dirent(){
    char* path = ".";
    DIR *dp; // 返回目录对象，类似于FILE*
    struct dirent *dirp;
    dp = opendir(path);
    while ((dirp = readdir(dp)) != NULL)
        printf("%s\n", dirp->d_name, dirp->);
    closedir(dp);
}

#define ForbiddenStatement(stmt) _Static_assert(0, "forbidden statement "#stmt)
#define sprintf(...) ForbiddenStatement(sprintf) 
#define BUFFSIZE 4096

void demo_stdio(){
   int n;
   char buf[BUFFSIZE];
   while ((n=read(STDIN_FILENO,buf,BUFFSIZE))>0)
   {
        if (write(STDOUT_FILENO, buf, n) != n)
            err_sys("write error");
   }
}

void demo_unbuffered_io(){
    /*
     * <stdio.h>
     * stdin, stdout, stderr
     * EOF
     *
     */
    int c;
    while ((c = getc(stdin)) != EOF)
        if (putc(c,stdout) == EOF)
            err_sys("output error");
    if (ferror(stdin))
        err_sys("input error");
   /*
    * sprintf
    * snprintf 
    * vsnprintf
    *
    */
}
/*
 * unistd.h
 *
 *
 *
 */
void demo_unistd(){
    printf("%d\n%d\n%d\n", STDIN_FILENO,STDOUT_FILENO,STDERR_FILENO);
}

#define println(x) _Generic((x), int: printf("%d\n", x),double: printf("%lf\n", x))

void demo_generic(){
    println(1);
    println(1.0);
}

int main(){
    separator(demo_generic);
    demo_generic();
    //separator(io);
    //demo_stdio();
    separator(getpid);
    printf("%d\n", getpid());
    separator(demo_dirent);
    demo_dirent();
    separator(demo_unistd);
    demo_unistd();

}

