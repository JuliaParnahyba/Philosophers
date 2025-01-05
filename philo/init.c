/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:22:25 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/05 18:31:35 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Function to initialize the simulation
void start_simulation(t_table *table)
{
    int i;

    table->start_time = get_current_time(); // Get the current time, marc the start of the simulation
    i = 0;
    while (i < table->num_philosophers)
    {
        // Atualiza o tempo da última refeição no início da simulação
        table->philosophers[i].last_meal_time = table->start_time;
        pthread_create(&table->philosophers[i].thread, NULL,
                       philosopher_life, &table->philosophers[i]);
        i++;
    }
    i = 0;
    while (i < table->num_philosophers)
    {
        pthread_join(table->philosophers[i].thread, NULL);
        i++;
    }
}

void *monitor_life(void *arg)
{
    t_table *table;
    int     i;

    table = (t_table *)arg;
    i = 0;
    while (!table->stop_simulation)
    {
        if (i == table->num_philosophers - 1)
            i = 0;
        pthread_mutex_lock(&table->meal_lock);
        if (table->philosophers_done == table->num_philosophers)
        {
            table->stop_simulation = 1;
            pthread_mutex_unlock(&table->meal_lock);
            return (NULL);
        }
        pthread_mutex_unlock(&table->meal_lock);
        if ((get_current_time() - table->philosophers[i].last_meal_time) > table->time_to_die)
        {
            table->stop_simulation = 1;
            pthread_mutex_lock(&table->print_lock);
            print_action(table->philosophers[i].id, "died");
            pthread_mutex_unlock(&table->print_lock);
            return (NULL);
        }
        i++;
        usleep(1000); // Pequeno delay para evitar uso excessivo de CPU
    }
    return (NULL);
}

// Function to initialize the table
int init_table(t_table *table, int argc, char **argv)
{
    int i;

    //parse of arguments
    table->num_philosophers = ft_atoi(argv[1]);
    table->time_to_die = ft_atoi(argv[2]);
    table->time_to_eat = ft_atoi(argv[3]);
    table->time_to_sleep = ft_atoi(argv[4]);
    if (argc == 6)
        table->meals_required = ft_atoi(argv[5]);
    else
        table->meals_required = -1;
    table->stop_simulation = 0;
    table->philosophers_done = 0;

    pthread_mutex_init(&table->print_lock, NULL);
    pthread_mutex_init(&table->meal_lock, NULL); // Inicializa o mutex para refeições

    //memory allocation for forks and philosophers
    table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
    table->philosophers = malloc(sizeof(t_philosopher) * table->num_philosophers);
    if (!table->forks || !table->philosophers)
        return (1);

    //initialization of mutex(forks) and philosophers
    i = 0;
    while (i < table->num_philosophers)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        table->philosophers[i].id = i + 1;
        table->philosophers[i].left_fork = &table->forks[i];
        table->philosophers[i].right_fork = &table->forks[(i + 1) % table->num_philosophers];
        table->philosophers[i].last_meal_time = 0;
        table->philosophers[i].meals_eaten = 0;
        table->philosophers[i].table = table;
        i++;
    }
    return (0);
}