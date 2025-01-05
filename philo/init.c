/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:22:25 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/05 01:41:44 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void start_simulation(t_table *table)
{
    int i;

    table->start_time = get_current_time();
    i = 0;
    while (i < table->num_philosophers)
    {
        pthread_create(&table->philosophers[i].thread, NULL,
                       philosopher_routine, &table->philosophers[i]);
        pthread_detach(table->philosophers[i].thread);  // Desanexar a thread após criação
        i++;
    }
    if (table->stop_simulation)
    {
        i = 0;
        while (i < table->num_philosophers)
        {
            pthread_cancel(table->philosophers[i].thread);
            i++;
        }
    }
}

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

    //memory allocation for forks and philosophers
    table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philosophers);
    table->philosophers = malloc(sizeof(t_philosopher) * table->num_philosophers);
    if (!table->forks || !table->philosophers)
        return (1);

    //initialization of mutex(print_lock) e stop_simulation
    pthread_mutex_init(&table->print_lock, NULL);
    table->stop_simulation = 0;

    //initialization of mutex(forks) and philosophers
    i = 0;
    while (i < table->num_philosophers)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        table->philosophers[i].id = i + 1;
        table->philosophers[i].left_fork = &table->forks[i];
        table->philosophers[i].right_fork = &table->forks[(i + 1) % table->num_philosophers];
        table->philosophers[i].meals_eaten = 0;
        table->philosophers[i].last_meal_time = get_current_time();  // Inicializar corretamente
        table->philosophers[i].table = table;
        i++;
    }
    return (0);
}