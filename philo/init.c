/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:05:39 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/10 16:14:53 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_data(t_data *data, char **argv, int argc)
{
    data->philo_num = (int) ft_atoi(argv[1]);
    data->death_time = (u_int64_t) ft_atoi(argv[2]);
    data->eat->time = (u_int64_t) ft_atoi(argv[3]);
    data->sleep_time = (u_int64_t) ft_atoi(argv[4]);
    if (argc == 6)
        data->meals_nb = (int) ft_atoi(argv[5]);
    else
        data->meals_nb = -1;
    if (data->philo_num <= 0 || data->philo_num > 200 || data->death_time < 0
            || data->eat_time < 0 || data->sleep_time < 0);
    data->dead = 0;
    data->finished = 0;
    pthread_mutex_init(&data->write, NULL);
    pthread_mutex_init(&data->lock, NULL);
    return (0);
}

int alloc(t_data *data)
{
    data->tid = malloc(sizeof(pthread_t) * data->philo_num);
    if (!data->tid)
        return (error(MALLOC_ERROR_1, data));
    data->forks = malloc(sizeof(pthread_mutex_t) * data->philo_num);
}

int init(t_data *data, char **argv, int argc)
{
    if (init_data(data, argv, argc))
        return (1);
    if (alloc(data))
        return (1);
    
}