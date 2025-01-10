/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:48:49 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/10 15:30:27 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void one_philo(t_table *table)
{
    table->time_to_start = get_time();
    if (pthread_create(&table->threads_id[0], NULL, &the_routine, &table->philos[0]))
    {
        print_error(PTHREAD_ERROR_THR, table);
        return ;
    }
    pthread_detach(table->threads_id[0]);
    while (table->dead == 0)
        ft_usleep(0);
    destroy_table(table);
    return ;
}

int validate_args(int argc, char **argv)
{
    int i;

    i = 1;
    if (ft_atoi(argv[1]) > 200)
    {
        print_error(INPUT_ERROR_4, NULL);
        return (1);
    }
    if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
    {
        print_error(INPUT_ERROR_5, NULL);
        return (1);
    }
    while (i < argc)
    {
        if (ft_atoi(argv[i]) <= 0)
        {
            print_error(INPUT_ERROR_2, NULL);
            return (1);
        }
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_table table;

    if (argc < 5 || argc > 6)
    {
        print_error(INPUT_ERROR_3, NULL);
        return (1);
    }
    if (validate_args(argc, argv))
    {
        print_error(INPUT_ERROR_1, NULL);
        return (1);
    }
    if (init_dnr(&table, argc, argv))
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
