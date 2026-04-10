#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>

void handler_sigusr1(int sigusr1){
    printf("SIGUSR reçu par %u\n", getpid());
    fflush(stdout);
}
int main (int argc, char* argv[]){
    struct sigaction sa;
    sa.sa_handler = &handler_sigusr1;
    sa.sa_flags =SA_RESTART;
    sigemptyset(&sa.sa_mask);

    if(sigaction(SIGUSR1, &sa, NULL) == -1){
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        time_t currentTime;
        time(&currentTime);
        
        printf("Mon numero est %u, il est %s \n", getpid(),ctime(&currentTime));
        
        sleep(1);

    }
    return 0;
}