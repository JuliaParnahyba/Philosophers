#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

pthread_mutex_t fork_mutex;

void *philosopher(void *arg) 
{
    int id = *(int *)arg;
    //tentativa de pegar os garfos
    pthread_mutex_lock(&fork_mutex);
    printf("Philosopher %d take a fork.\n", id);

    //comer
    printf("Philosopher %d is eating.\n", id);
    pthread_mutex_unlock(&fork_mutex);

    // pensar ou devolver os garfos
    printf("Philosopher %d is thinking.\n", id);
    return NULL;
}

int init_philosophers(int nbr_philosophers)
{
    int i = 0;

    //memory allocation for the philosophers
    pthread_t *philosophers = malloc (sizeof(pthread_t) * nbr_philosophers);
    //memory allocation for the philosophers id
    int *philosophers_id = malloc (sizeof(int) * nbr_philosophers);
    //initialize the mutex
    pthread_mutex_init(&fork_mutex, NULL);
    //create the philosophers
    while (i < nbr_philosophers) //for each philosopher
    {
        philosophers_id[i] = i + 1; //set the philosopher id
        //create the philosopher thread
        if (pthread_create(&philosophers[i], NULL, philosopher, &philosophers_id[i]))
        {
            printf("Error creating philosopher %d.\n", i);
            free(philosophers); //free the philosophers memory
            free(philosophers_id); //free the philosophers id memory
            return (1); //return an error
        }
        i++;
    }
    i = 0;
    //wait for the philosophers to finish
    while (i < nbr_philosophers)
    {
        //wait for the philosopher thread to finish
        pthread_join(philosophers[i], NULL);
        i++;
    }
    //destroy the mutex
    pthread_mutex_destroy(&fork_mutex);
    //free the philosophers memory
    free(philosophers);
    //free the philosophers id memory
    free(philosophers_id);
    //return success
    return (0);
}

int main(int argc, char *argv[]) 
{
    if (argc < 2)
    {
        printf("Usage: %s <number of philosophers>\n", argv[0]);
        return 1;
    }
    // convert string to integer for the number of philosophers
    int nbr_philosophers = atoi(argv[1]); 

    // check if the number of philosophers is a positive integer
    if (nbr_philosophers <= 0) 
    {
        printf("The number of philosophers must be a positive integer.\n");
        return 1;
    }
    init_philosophers(nbr_philosophers);
    return 0;
}