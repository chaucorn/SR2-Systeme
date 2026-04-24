#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <pthread.h>



typedef struct
{
    int rang;
    int nf;
}t_args;

void *activate(void *arg)
{
    t_args *a = (t_args *) arg;

    srand(time(NULL) ^ pthread_self());
    for (int j = 0; j < count; j++)
    {
        struct timespec delai;
        delai.tv_sec = 0;
        delai.tv_nsec = (rand() % 100 + 1)*1000000;
        nanosleep(&delai, NULL);
        printf("Activite rang %d : identifiant = %lu (delai = %ld ms)\n ", a->rang, pthread_self(), delai.tv_nsec / 1000000);
    }
    pthread_exit((void *)(long)a->rang);

}
int main (int argc, char* argv[])
{
    if (argc != 3){
        fprintf(stderr, "Usage: %s nb_activite nb_fois \n ", argv[0]);
        return 1;
    }
    int NA = atoi(argv[1]);
    int NF = atoi(argv[2]);

    pthread_t tids[NA];
    t_args args[NA];

    for (int i = 0; i< NA; i++)
    {
        args[i].rang = i;
        args[i].nf = NF;
        if (pthread_create(&tids[i], NULL, activite, &args[i]) != 0)
        {
            perror("pthread_create");
            return 2;
        }
        
    }
    

    for (int i = 0; i < NA; i++)
    {
        void *retval;
        pthread_join(tids[i], &retval);
        printf("Valeur retournee par le thread %lu = %ld\n",
               tids[i], (long)retval);
    }
    
    

    return 0;
    

}