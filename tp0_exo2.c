#define _POSIX_C_SOURCE 200809L
#include <stdio.h>      //printf
#include <stdlib.h>     // exit
#include <sys/types.h>  //pid_t,
#include <unistd.h>     //fork, getpid
#include <sys/wait.h>   //wexitstatus

int main (int argc, char* argv[]){
    int fd[2];
    // fd[0] read
    // fd[1] write
    if (pipe(fd) == -1)
    {
        printf("pipe error\n");
        return 1;
    }
    int id = fork();
    if (id == 0)
    {
        close(fd[0]);
        int x;
        printf("INput a number:\n");
        scanf("%d", &x);
        write(fd[1], &x, sizeof(int));
        close(fd[1]);
    }else{
        close(fd[1]);
        int y;
        read(fd[0], &y, sizeof(int));
        close(fd[0]);
        printf("Got from child process: %d\n", y);
    }



    return 0;
}