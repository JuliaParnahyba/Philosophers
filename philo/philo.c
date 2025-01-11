#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//mutex for the forks
pthread_mutex_t *fork_mutex;

// global variables
int max_meals;
int nbr_philosophers;

void printf_status(int id, char *status)
{
    printf("Philosopher %d %s\n", id + 1 , status);
}

void *routine(void *arg)
{
    int id = *(int *)arg;
    int meals = 0;

    while (1)
    {
        //a diferent way to take the fork for the last philosopher
        if (id % 2 == 0)
        {
            //to take a fork, the philosopher must lock the mutex
            pthread_mutex_lock(&fork_mutex[id]);
            printf_status(id, "has taken the left fork.");
            pthread_mutex_lock(&fork_mutex[(id + 1) % nbr_philosophers]);
            printf_status(id, "has taken the right fork.");
        }
        else
        {
            //to take a fork, the philosopher must lock the mutex
            pthread_mutex_lock(&fork_mutex[(id + 1) % nbr_philosophers]);
            printf_status(id, "has taken the right fork.");
            pthread_mutex_lock(&fork_mutex[id]);
            printf_status(id, "has taken the left fork.");
        }
        //to eat, the philosopher must lock the mutex
        printf_status(id, "is eating");
        usleep(1000 * 500);
        meals++;

        //to put the fork, the philosopher must lock the mutex
        pthread_mutex_unlock(&fork_mutex[id]);
        pthread_mutex_unlock(&fork_mutex[(id + 1) % nbr_philosophers]);
        printf_status(id, "has put down the forks.");

        //to sleep, the philosopher must lock the mutex
        printf_status(id, "is sleeping.");
        usleep(1000 * 500);

        //to think, the philosopher must lock the mutex
        printf_status(id, "is thinking.");

        if (max_meals != -1 && meals >= max_meals)
        {
            printf_status(id, "has finished his meals.");
            return NULL;
        }
    }
    return NULL;
}

int init_philosophers(int nbr_philosophers, int meals)
{
    max_meals = meals;
    int i = 0;

    //memory allocation for the mutex
    fork_mutex = malloc(sizeof(pthread_mutex_t) * nbr_philosophers);
    if (!fork_mutex)
    {
        printf("Error allocating memory for the mutex.\n");
        return (1);
    }

    //initialize the mutex
    while (i < nbr_philosophers)
    {
        pthread_mutex_init(&fork_mutex[i], NULL);
        i++;
    }

    //memory allocation for the philosophers
    pthread_t *philosophers = malloc (sizeof(pthread_t) * nbr_philosophers);
    //memory allocation for the philosophers id
    int *philosophers_id = malloc (sizeof(int) * nbr_philosophers);

    if (!philosophers || !philosophers_id)
    {
        printf("Error allocating memory for philosophers.\n");
        return (1);
    }

    i = 0;
    //create the philosophers
    while (i < nbr_philosophers) //for each philosopher
    {
        philosophers_id[i] = i; //set the philosopher id
        //create the philosopher thread
        if (pthread_create(&philosophers[i], NULL, routine, &philosophers_id[i]))
        {
            printf("Error creating philosopher %d.\n", i);
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

    i = 0;
    //destroy the mutex
    while (i < nbr_philosophers)
    {
        pthread_mutex_destroy(&fork_mutex[i]);
        i++;
    }
    //free the philosophers memory
    free(philosophers);
    //free the philosophers id memory
    free(philosophers_id);
    //return success
    free(fork_mutex);
    return (0);
}

int main(int argc, char **argv) 
{
    int meals = 0;
    if (argc < 2)
    {
        printf("Usage: %s <number of philosophers> <max meals>\n", argv[0]);
        return 1;
    }
    if (argc == 3)
        meals = atoi(argv[2]);
    else
        meals = -1;
    // convert string to integer for the number of philosophers
    nbr_philosophers = atoi(argv[1]); 
    

    // check if the number of philosophers is a positive integer
    if (nbr_philosophers <= 0 || (argc == 3 && meals <= 0)) 
    {
        printf("The number of philosophers must be a positive integer.\n");
        return 1;
    }
    
    return init_philosophers(nbr_philosophers, meals);
}