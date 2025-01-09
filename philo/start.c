/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:50:40 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/09 14:41:35 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int start_simulation(t_table *table)
{
    pthread_t   *thr;
    int         i;

    i = 0;
    thr = (pthread_t *)malloc(sizeof(pthread_t));
    table->time_to_start = get_time();
    if (table->nb_must_eat > 0)
    {
        if (pthread_create(thr, NULL, &philo_life, &table->philos[0]))
        {
            print_error(PTHREAD_ERROR_THR, table);
            return (1);
        }
    }
    while (i < table->nb_philo)
    {
        if (pthread_create(&table->threads[i], NULL, &the_routine, &table->philos[i]))
        {
            print_error(PTHREAD_ERROR_THR, table);
            return (1);
        }
        ft_usleep(1);
        i++;
    }
    i = 0;
    while (i < table->nb_philo)
    {
        if (pthread_join(table->threads[i], NULL))
        {
            print_error(PTHREAD_ERROR_JOIN, table);
            return (1);
        }
        i++;
    }
    return (0);
}
