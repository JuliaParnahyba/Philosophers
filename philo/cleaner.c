/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:59:18 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/10 16:01:38 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    clear_data(t_data *data)
{
    if (data->tid)
        free(data->tid);
    if (data->forks)
        free(data->forks);
    if (data->philos)
        free(data->philos);
}

void    ft_exit(t_data *data)
{
    int i;

    i = -1;
    while (++i < data->philo_num)
    {
        pthread_mutex_destroy(&data->forks[i]);
        pthread_mutex_destroy(&data->philos[i].lock);
    }
    pthread_mutex_destroy(&data->write);
    pthread_mutex_destroy(&data->lock);
    clear_data(data);
}
