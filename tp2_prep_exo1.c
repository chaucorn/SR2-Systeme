#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

int main(int argc, char*argv[]){
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s nombre_de_fois\n", argv[0]);
        return 1;
    }
    int NE = atoi(argv[1]);

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
        char message[20];
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
            printf("Pere: Message %i envoyé\n", i);
            if (write(fd[1], mess, strlen(mess)) < 0)
            {
                close(fd[1]);
                return 5;
            }       
        }

        close(fd[1]);
        wait(NULL);
        printf("Pere: je me termine dernier\n");
    }
    
    return 0;
    
}