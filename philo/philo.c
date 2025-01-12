#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

//mutex for the forks
pthread_mutex_t *fork_mutex;
//mutex for the meals
pthread_mutex_t meals_mutex;
//mutex para proteger a variável simulation_over
pthread_mutex_t simulation_mutex;

// global variables
int         max_meals; // maximum number of meals
int         nbr_philosophers; // number of philosophers
int         time_to_died; // time to died in milliseconds
int         time_to_eat; // time to eat in milliseconds
int         time_to_sleep; // time to sleep in milliseconds
int         simulation_over; // flag to check if the simulation is over
int         *meals_count; // array to store the number of meals for each philosopher
long long   *last_meal_time; // array to store the last meal time for each philosopher


long long current_time_in_ms()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (long long)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void print_status(int id, char *status)
{
    printf("Philosopher %d %s\n", id + 1 , status);
}

void    take_forks(int id)
{
    //a diferent way to take the fork for the last philosopher
    if (id % 2 == 0)
    {
        //to take a fork, the philosopher must lock the mutex
        pthread_mutex_lock(&fork_mutex[id]);
        print_status(id, "has taken the left fork.");
        pthread_mutex_lock(&fork_mutex[(id + 1) % nbr_philosophers]);
        print_status(id, "has taken the right fork.");
    }
    else
    {
        //to take a fork, the philosopher must lock the mutex
        pthread_mutex_lock(&fork_mutex[(id + 1) % nbr_philosophers]);
        print_status(id, "has taken the right fork.");
        pthread_mutex_lock(&fork_mutex[id]);
        print_status(id, "has taken the left fork.");
    }
}

void    eat(int id)
{
    //to eat, the philosopher must lock the mutex
    print_status(id, "is eating");
    usleep(1000 * time_to_eat);

    //protect the meals count with a mutex
    pthread_mutex_lock(&meals_mutex);
    meals_count[id]++;
    last_meal_time[id] = current_time_in_ms();
    pthread_mutex_unlock(&meals_mutex);
}

void    put_forks(int id)
{
    //to put the fork, the philosopher must lock the mutex
    pthread_mutex_unlock(&fork_mutex[id]);
    pthread_mutex_unlock(&fork_mutex[(id + 1) % nbr_philosophers]);
    print_status(id, "has put down the forks.");
}

void    sleeping(int id)
{
    //to sleep, the philosopher must lock the mutex
    print_status(id, "is sleeping.");
    usleep(1000 * time_to_sleep);
}

void    thinking(int id)
{
    //to think, the philosopher must lock the mutex
    print_status(id, "is thinking.");
}

void    *monitor(void *arg)
{
    int         i;
    int         all_finished;
    long long   time_since_last_meal;
    long long   current_time;

    i = 0;
    while (1)
    {
        pthread_mutex_lock(&simulation_mutex);
        if (simulation_over)
        {
            pthread_mutex_unlock(&simulation_mutex);
            return NULL;
        }
        pthread_mutex_unlock(&simulation_mutex);

        i = 0;
        all_finished = 1;
        while (i < nbr_philosophers)
        {
            //protect the meals count with a mutex
            pthread_mutex_lock(&meals_mutex);
            current_time = current_time_in_ms();
            time_since_last_meal = current_time - last_meal_time[i];

            //check if the philosopher has died
            if (time_since_last_meal > time_to_died)
            {
                print_status(i, "has died.");
                pthread_mutex_lock(&simulation_mutex);
                simulation_over = 1;
                pthread_mutex_unlock(&simulation_mutex);
                pthread_mutex_unlock(&meals_mutex);
                return NULL;
            }
            
            //check if all philosophers have finished eating
            if (max_meals != -1 && meals_count[i] < max_meals)
                all_finished = 0;
            pthread_mutex_unlock(&meals_mutex);
            i++;
        }

        //if all philosophers have finished eating, end the simulation
        if (max_meals != -1 && all_finished)
        {
            pthread_mutex_lock(&simulation_mutex);
            simulation_over = 1;
            pthread_mutex_unlock(&simulation_mutex);
            return NULL;
        }

        usleep(50); //check every 1ms
    }
    return NULL;
}

void    *routine(void *arg)
{
    int id;

    id = *(int *)arg;
    pthread_mutex_lock(&meals_mutex);
    last_meal_time[id] = current_time_in_ms();
    pthread_mutex_unlock(&meals_mutex);

    while (1)
    {
        pthread_mutex_lock(&simulation_mutex);
        if (simulation_over)
        {
            pthread_mutex_unlock(&simulation_mutex);
            break ;
        }
        pthread_mutex_unlock(&simulation_mutex);

        take_forks(id);
        eat(id);
        put_forks(id);
        sleeping(id);
        thinking(id);
    }
    return NULL;
}

int init_philosophers(int nbr_philosophers, int meals)
{
    int         i;
    int         *philosophers_id;
    pthread_t   *philosophers;
    pthread_t   monitor_thread;

    i = 0;

    //initialize the max meals mutex
    pthread_mutex_init(&meals_mutex, NULL);

    //memory allocation for the meals count
    meals_count = malloc(sizeof(int) * nbr_philosophers);
    //memory allocation for the last meal time
    last_meal_time = malloc(sizeof(long long) * nbr_philosophers);
    //memory allocation for the mutex
    fork_mutex = malloc(sizeof(pthread_mutex_t) * nbr_philosophers);
    if (!meals_count || !fork_mutex || !last_meal_time)
    {
        printf("Error allocating memory for the meals count.\n");
        return (1);
    }

    //initialize the meals count
    while (i < nbr_philosophers)
    {
        last_meal_time[i] = current_time_in_ms();
        pthread_mutex_init(&fork_mutex[i], NULL);
        i++;
    }

    //create the monitor thread
    if (pthread_create(&monitor_thread, NULL, monitor, NULL))
    {
        printf("Error creating monitor thread.\n");
        return (1);
    }

    //memory allocation for the philosophers
    philosophers = malloc (sizeof(pthread_t) * nbr_philosophers);
    //memory allocation for the philosophers id
    philosophers_id = malloc (sizeof(int) * nbr_philosophers);

    if (!philosophers || !philosophers_id)
    {
        printf("Error allocating memory for philosophers.\n");
        return (1);
    }

    i = 0;
    //create the philosophers threads
    while (i < nbr_philosophers) //for each philosopher
    {
        philosophers_id[i] = i; //set the philosopher id
        //create the philosopher thread
        if (pthread_create(&philosophers[i], NULL, routine, &philosophers_id[i]))
        {
            printf("Error creating philosopher %d.\n", i);
            return (1);
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

    //wait for the monitor thread to finish
    pthread_join(monitor_thread, NULL);

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
    //free the mutex memory
    free(fork_mutex);
    //free the meals count memory
    free(meals_count);
    //free the last meal time memory
    free(last_meal_time);

    //destroy the mutex
    pthread_mutex_destroy(&meals_mutex);

    //destroy the mutex
    pthread_mutex_destroy(&simulation_mutex);

    //return success
    return (0);
}

int check_input(int argc, char **argv)
{
    int i = 1;
    if (argc < 5 || argc > 6)
    {
        printf("Usage: %s <number of philosophers> <time_to_eat> <time_to_sleep> [max meals]\n", argv[0]);
        return 1;
    }
    while (i < argc)
    {
        if (atoi(argv[i]) <= 0)
        {
            printf("All arguments must be a positive integer.\n");
            return (1);
        }
        i++;
    }
    return 0;
}

int main(int argc, char **argv) 
{
    if (check_input(argc, argv))
        exit(1);

    // convert string to integer 
    // number of philosophers
    nbr_philosophers = atoi(argv[1]);
    // time to died
    time_to_died = atoi(argv[2]);
    // time to eat
    time_to_eat = atoi(argv[3]);
    // time to sleep
    time_to_sleep = atoi(argv[4]);

    // check if has the number of meals
    if (argc == 6)
        max_meals = atoi(argv[5]);
    else
        max_meals = -1;

    simulation_over = 0;
    pthread_mutex_init(&simulation_mutex, NULL);
    
    return init_philosophers(nbr_philosophers, max_meals);
}