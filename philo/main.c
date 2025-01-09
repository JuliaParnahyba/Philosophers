/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:48:49 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/09 14:53:58 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int one_philo(t_table *table)
{
    table->time_to_start = get_time();
    if (pthread_create(&table->threads[0], NULL, &philo_life, &table->philos[0]))
    {
        print_error(PTHREAD_ERROR_THR, table);
        return (1);
    }
    pthread_detach(table->threads[0]);
    while (table->dead == 0)
        ft_usleep(0);
    destroy_table(table);
    return (0);
}

int validate_args(int argc, char **argv)
{
    int i;

    i = 1;
    if (ft_atoi(argv[1]) > 200)
    {
        printf("Error: Number of Phisopher must be lower then 200\n");
        return (1);
    }
    if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
    {
        printf("Error: time values must be at least 60ms\n");
        return (1);
    }
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
    t_table table;

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
    if (init(&table, argc, argv))
        return (1);
    if (table.nb_philo == 1)
    {
        one_philo(&table);
        return (0);
    }
    if (start_simulation(&table))
        return (1);
    destroy_table(&table);
    return (0);
}