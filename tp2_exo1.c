#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

volatile sig_atomic_t envois_effectues = 0;
volatile sig_atomic_t signal_recu = 0;

void handler_sigalrm(int sig){
    (void) sig;
    signal_recu = 1;
}


int main(int argc, char*argv[]){
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s interval_seconde nombre_de_fois\n", argv[0]);
        return 1;
    }
    int delai = atoi(argv[1]);
    int nb_envois = atoi(argv[2]);
    int count = 0;
    int fd[2];
    if(pipe(fd) == -1){
        return 2;
    }
    
    pid_t pid = fork();


    if (pid == -1)
    {
        perror("pid");
        return 3;
    }
    else if (pid == 0)
    {
        close(fd[1]); //close for write
        char* message[20];
        ssize_t n;
        while ((n = read(fd[0], message, sizeof(message) - 1)) > 0) {
            message[n] = '\0';
            printf("Fils: recu de mon pere: %s\n", message);
        }
        close(fd[0]);
        printf("Fils: je me termine\n");
        return 0;
        
            

    }else{ //pere
        
        char* mess = "je suis ton pere\n";
        for (int i = 0; i < NE; i++)
        {
            close(fd[0]);

            struct sigaction sa;
            sa.sa_handler = handler_sigalrm;
            sigemptyset(&sa.sa_mask);
            sa.sa_flags = 0;

            if (sigaction(SIGALRM, &sa, NULL) == -1)
            {
                perror("sigaction");
                close(fd[1]);
                return 4;
            }
            alarm(delai);

            while (envois_effectues < nb_envois)
            {
                if (signal_recu)
                {
                    signal_recu = 0;
                    envois_effectues ++;

                    char message[100];
                    snprintf(message, sizeof(message), "message numero %d\n"; envois_effectues);
                    if (write(fd[1]))
                    {
                        /* code */
                    }
                    
                }
                
            }
            

            
        }

        close(fd[1]);
        wait(NULL);
        printf("Pere: je me termine dernier\n");
    }
    
    return 0;
    
}