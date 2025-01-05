/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:21:36 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/05 13:45:16 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_table(t_table *table)
{
    int i;

    i = 0;
    while (i < table->num_philosophers)
    {
        pthread_mutex_destroy(&table->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&table->print_lock);
    pthread_mutex_destroy(&table->meal_lock);  // Destrói o mutex meal_lock
    free(table->forks);
    free(table->philosophers);
}

int validate_args(int argc, char **argv)
{
    int i;

    i = 1;
    while (i < argc)
    {
        if (ft_atoi(argv[i]) <= 0)
            return (1);
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_table     table;
    pthread_t   monitor;

    if (argc < 5 || argc > 6)
    {
        printf("Error: wrong number of arguments\n");
        return (1);
    }
    if (validate_args(argc, argv))
    {
        printf("Error: invalid arguments\n");
        return (1);
    }
    if (init_table(&table, argc, argv))
    {
        printf("Error: failed to initialize table\n");
        return (1);
    }
    pthread_create(&monitor, NULL, monitor_life, &table);
    start_simulation(&table);
    pthread_join(monitor, NULL);

    free_table(&table);
    
    printf("Simulation ended\n");
    return (0);
}