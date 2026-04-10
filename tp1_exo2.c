#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

void handler_sigint(int sigusr1){
    printf("SIGINT reçu par %u\n", getpid());
    fflush(stdout);
}
int main (int argc, char* argv[]){
    struct sigaction sa;
        sa.sa_handler = &handler_sigint;
        sa.sa_flags =SA_RESTART;
        sigemptyset(&sa.sa_mask);

        if(sigaction(SIGINT, &sa, NULL) == -1){
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
    
    pid_t pid;
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }


    if (pid == 0) // fils
    {
        
        while (1)
        {
            time_t currentTime;
            time(&currentTime);
            
            printf("Mon numero est %u, il est %s \n", getpid(),ctime(&currentTime));
            
            sleep(1);

        }
    }
    int status;
    pid_t child_pid = wait(&status);
    printf("le pere\n");
    if (child_pid > 0 && WIFEXITED(status)) {
        printf("Valeur retournee par le fils %d = %d\n",
                child_pid, WEXITSTATUS(status));
        fflush(stdout);
    }

    
    
}