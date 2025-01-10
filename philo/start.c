/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:40 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/10 13:30:16 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int start_simulation(t_table *table)
{
    pthread_t   thrd;
    int         i;

    i = 0;
    table->time_to_start = get_time();
    if (table->nb_must_eat > 0)
    {
        if (pthread_create(&thrd, NULL, &philo_life, &table->philos[0]))
        {
            print_error(PTHREAD_ERROR_THR, table);
            return (1);
        }
    }
    while (i < table->nb_philo)
    {
        if (pthread_create(&table->threads_id[i], NULL, &the_routine, &table->philos[i]))
        {
            print_error(PTHREAD_ERROR_THR, table);
            return (1);
        }
        ft_usleep(10);
        i++;
    }
    i = 0;
    while (i < table->nb_philo)
    {
        if (pthread_join(table->threads_id[i], NULL))
        {
            print_error(PTHREAD_ERROR_JOIN, table);
            return (1);
        }
        i++;
    }
    return (0);
}
