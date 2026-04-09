#define _POSIX_C_SOURCE 200809L
#include <stdio.h>      //printf
#include <stdlib.h>     // exit
#include <sys/types.h>  //pid_t,
#include <unistd.h>     //fork, getpid
#include <sys/wait.h>   //wexitstatus


int main (int argc, char* argv[]){
    if (argc!=3){
        fprintf(stderr,"Usage: %s nb_fils nb_fois\n", argv[0]);
        exit(1);
    }

    int NF = atoi(argv[1]);
    int NM = atoi(argv[2]);

    for (int i = 0; i < NF; i++)
    {
        pid_t pid = fork();
        if ((pid <0))
        {
            perror("fork");
            return 1;
        }
        
        if (pid == 0)
        {
            int rang = i + 1;
            for (int j = 0; j < NM; j++) {
                printf("Activite rang %d identifiant = %u\n",
                       rang, getpid());
                //fflush(stdout);
                }
                sleep(1);   
                exit(rang);
        }
        
        
    }
    printf("code parent\n");
    for (int i = 0; i < NF; i++) {
        int status;
        pid_t child_pid = wait(&status);

        if (child_pid > 0 && WIFEXITED(status)) {
            printf("Valeur retournee par le fils %d = %d\n",
                   child_pid, WEXITSTATUS(status));
            fflush(stdout);
        }
    }
}