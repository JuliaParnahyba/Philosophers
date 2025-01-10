/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:32:04 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/10 15:21:48 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int allocation(t_table *table)
{
    table->threads_id = malloc(sizeof(pthread_t) * table->nb_philo);
    if (!table->threads_id)
    {
        print_error(MALLOC_ERROR_1, table);
        return (1);
    }
    table->philos = malloc(sizeof(t_philo) * table->nb_philo);
    if (!table->philos)
    {
        print_error(MALLOC_ERROR_2, table);
        return (1);
    }
    table->forks = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
    if (!table->forks)
    {
        print_error(MALLOC_ERROR_3, table);
        return (1);
    }
    return (0);
}

int init_forks(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nb_philo)
    {
        pthread_mutex_init(&table->forks[i], NULL);
        i++;
    }
    table->philos[0].left_fork = &table->forks[0];
    table->philos[0].right_fork = &table->forks[table->nb_philo - 1];
    i = 1;
    while (i < table->nb_philo)
    {
        table->philos[i].left_fork = &table->forks[i];
        table->philos[i].right_fork = &table->forks[i - 1];
        i++;
    }
    return (0);
}

int init_philos(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nb_philo)
    {
        table->philos[i].table = table;
        table->philos[i].id = i + 1;
        table->philos[i].count_eat = 0;
        table->philos[i].last_meal = 0;
        table->philos[i].eating = 0;
        table->philos[i].the_death = table->time_to_die;
        pthread_mutex_init(&table->philos[i].meal_lock, NULL);
        i++;
    }
    return (0);
}

int init_table(t_table *table, int argc, char **argv)
{
    table->nb_philo = (int) ft_atoi(argv[1]);
    table->time_to_die = (u_int64_t) ft_atoi(argv[2]);
    table->time_to_eat = (u_int64_t) ft_atoi(argv[3]);
    table->time_to_sleep = (u_int64_t) ft_atoi(argv[4]);
    if (argc == 6)
        table->nb_must_eat = (int) ft_atoi(argv[5]);
    else
        table->nb_must_eat = -1;
    table->dead = 0;
    table->the_end = 0;
    pthread_mutex_init(&table->print_lock, NULL);
    pthread_mutex_init(&table->table_lock, NULL);
    return (0);
}

int init_dnr(t_table *table, int argc, char **argv)
{
    if (init_table(table, argc, argv))
        return (1);
    if (allocation(table))
        return (1);
    if (init_forks(table))
        return (1);
    init_philos(table);
    return (0);
}