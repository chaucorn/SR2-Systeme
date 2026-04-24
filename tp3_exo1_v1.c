#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

int main (int argc, char* argv[]){
    if (argc != 3){
        fprintf(stderr, "Usage: %s nb_activite nb_fois \n ", argv[0]);
        return 1;
    }
    int NA = atoi(argv[1]);
    int NF = atoi(argv[2]);
    
    for (int i = 0; i < NA; i++)
    {
        pid_t pid = fork();

        if (pid == -1)
        {
            perror("fork");
            return 2;
        }
        if (pid == 0)
        {
            
            srand(time(NULL)^ getpid());
            
            for (int j = 0; j < NF; j++)
            {
                struct timespec delai;
                delai.tv_sec = 0;    
                delai.tv_nsec = (rand()%100 + 1)*1000000;
                nanosleep(&delai, NULL);

                printf("Activite rang %d : identifiant = %d (delai = %d ms)\n", i, getpid(), delai.tv_nsec/1000000);
            }
            exit(i);
        }   
    }
    for (int i = 0; i < NA; i++)
    {
        int status;
        pid_t pid ;

        while ((pid = wait(&status)) > 0)
        {
            if (WIFEXITED(status)){
                printf("Valeur retourne par le fils %d = %d \n", pid, WEXITSTATUS(status));
            }    
        }
        

        
        
    }
    return 0;
    

}