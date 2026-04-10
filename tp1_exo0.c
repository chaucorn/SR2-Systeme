#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>


int main (int argc, char* argv[]){
    if (argc != 3){
        fprintf(stderr, "Usage: %d NBS NBF\n", argv[0]);
        exit(1);
    }

    int NBS = atoi(argv[1]);
    int NBF = atoi(argv[2]);

    while (1)
    {
        time_t currentTime;
        time(&currentTime);
        for(int i = 0; i < NBF; i++){
            printf("Mon numero est %u, il est %s \n", getppid(),ctime(&currentTime));
        }
        sleep(NBS);

    }
    
}