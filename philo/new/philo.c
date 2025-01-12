// Arquivo: philosophers.h
#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_simulation {
    int num_philo;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int max_meals;
    int stop_simulation;
    pthread_mutex_t *forks;
    pthread_mutex_t death_mutex;
    pthread_mutex_t log_mutex;
    long start_time;
} t_simulation;

typedef struct s_philosopher {
    int id;
    int meals_eaten;
    long last_meal_time;
    pthread_t thread_id;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    t_simulation *sim_params;
} t_philosopher;

long current_time(void);
void ft_usleep(long time);
void log_action(t_philosopher *philo, char *action);
int init_simulation(t_simulation *sim, char **argv);
int init_philosophers(t_simulation *sim, t_philosopher **philos);
int start_simulation(t_simulation *sim, t_philosopher *philos);
void cleanup_simulation(t_simulation *sim, t_philosopher *philos);
void *philosopher_routine(void *arg);
void *monitor_routine(void *arg);

#endif

// Arquivo: init.c
#include "philosophers.h"

int init_simulation(t_simulation *sim, char **argv)
{
    int i;

    sim->num_philo = atoi(argv[1]);
    sim->time_to_die = atoi(argv[2]);
    sim->time_to_eat = atoi(argv[3]);
    sim->time_to_sleep = atoi(argv[4]);
    sim->max_meals = (argv[5]) ? atoi(argv[5]) : -1;
    sim->stop_simulation = 0;
    sim->forks = malloc(sizeof(pthread_mutex_t) * sim->num_philo);
    if (!sim->forks)
        return (1);
    i = 0;
    while (i < sim->num_philo)
    {
        pthread_mutex_init(&sim->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&sim->death_mutex, NULL);
    pthread_mutex_init(&sim->log_mutex, NULL);
    sim->start_time = current_time();
    return (0);
}

int init_philosophers(t_simulation *sim, t_philosopher **philos)
{
    int i;

    *philos = malloc(sizeof(t_philosopher) * sim->num_philo);
    if (!(*philos))
        return (1);
    i = 0;
    while (i < sim->num_philo)
    {
        (*philos)[i].id = i;
        (*philos)[i].meals_eaten = 0;
        (*philos)[i].last_meal_time = sim->start_time;
        (*philos)[i].left_fork = &sim->forks[i];
        (*philos)[i].right_fork = &sim->forks[(i + 1) % sim->num_philo];
        (*philos)[i].sim_params = sim;
        i++;
    }
    return (0);
}

// Arquivo: actions.c
#include "philosophers.h"

void eat(t_philosopher *philo)
{
    pthread_mutex_lock(philo->left_fork);
    log_action(philo, "has taken a fork");
    pthread_mutex_lock(philo->right_fork);
    log_action(philo, "has taken a fork");
    log_action(philo, "is eating");
    pthread_mutex_lock(&philo->sim_params->death_mutex);
    philo->last_meal_time = current_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->sim_params->death_mutex);
    ft_usleep(philo->sim_params->time_to_eat);
    pthread_mutex_unlock(philo->right_fork);
    pthread_mutex_unlock(philo->left_fork);
}

void think_and_sleep(t_philosopher *philo)
{
    log_action(philo, "is sleeping");
    ft_usleep(philo->sim_params->time_to_sleep);
    log_action(philo, "is thinking");
}

// Arquivo: utils.c
#include "philosophers.h"

long current_time(void)
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_usleep(long time)
{
    long start;

    start = current_time();
    while ((current_time() - start) < time)
        usleep(50);
}

void log_action(t_philosopher *philo, char *action)
{
    pthread_mutex_lock(&philo->sim_params->log_mutex);
    if (!philo->sim_params->stop_simulation)
        printf("%ld %d %s\n", current_time() - philo->sim_params->start_time, philo->id + 1, action);
    pthread_mutex_unlock(&philo->sim_params->log_mutex);
}

// Arquivo: monitor.c
#include "philosophers.h"

void *monitor_routine(void *arg)
{
    t_philosopher *philos;
    t_simulation *sim;
    int i;
    long time_since_last_meal;

    philos = (t_philosopher *)arg;
    sim = philos[0].sim_params;
    while (!sim->stop_simulation)
    {
        i = 0;
        while (i < sim->num_philo && !sim->stop_simulation)
        {
            pthread_mutex_lock(&sim->death_mutex);
            time_since_last_meal = current_time() - philos[i].last_meal_time;
            if (time_since_last_meal > sim->time_to_die)
            {
                log_action(&philos[i], "has died");
                sim->stop_simulation = 1;
            }
            pthread_mutex_unlock(&sim->death_mutex);
            i++;
        }
        usleep(1000);
    }
    return (NULL);
}

// Arquivo: main.c
#include "philosophers.h"

int start_simulation(t_simulation *sim, t_philosopher *philos)
{
    int i;
    pthread_t monitor;

    i = 0;
    while (i < sim->num_philo)
    {
        if (pthread_create(&philos[i].thread_id, NULL, philosopher_routine, &philos[i]))
            return (1);
        i++;
    }
    if (pthread_create(&monitor, NULL, monitor_routine, philos))
        return (1);
    i = 0;
    while (i < sim->num_philo)
    {
        pthread_join(philos[i].thread_id, NULL);
        i++;
    }
    pthread_join(monitor, NULL);
    return (0);
}

void cleanup_simulation(t_simulation *sim, t_philosopher *philos)
{
    int i;

    i = 0;
    while (i < sim->num_philo)
    {
        pthread_mutex_destroy(&sim->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&sim->death_mutex);
    pthread_mutex_destroy(&sim->log_mutex);
    free(sim->forks);
    free(philos);
}

int main(int argc, char **argv)
{
    t_simulation sim;
    t_philosopher *philos;

    if (argc < 5 || argc > 6 || init_simulation(&sim, argv) || init_philosophers(&sim, &philos))
    {
        printf("Invalid arguments or initialization failed\n");
        return (EXIT_FAILURE);
    }
    if (start_simulation(&sim, philos))
    {
        cleanup_simulation(&sim, philos);
        return (EXIT_FAILURE);
    }
    cleanup_simulation(&sim, philos);
    return (EXIT_SUCCESS);
}
