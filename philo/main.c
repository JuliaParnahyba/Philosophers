/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:51:06 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/10 16:05:28 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int case_one(t_data *data)
{
    data->start_time = get_time();
    if (pthread_create(&data->tid[0], NULL, &routine, &data->philos[0]))
        return (error(PTHREAD_ERROR_THR, data));
    pthread_deatch(data->tid[0]);
    while (data->dead == 0)
        ft_usleep(0);
    ft_exit(data);
    return (0);
}

int input_checker(int argc, char **argv)
{
    int i;

    i = 1;
    // Verifica se o número de filósofos é menor que 200
    if (ft_atoi(argv[1]) > 200)
    {
        error(INPUT_ERROR_1, NULL);
        return (1);
    }
    // Verifica se o tempo fornecido está abaixo de 60ms
    if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
    {
        error(INPUT_ERROR_5, NULL);
        return (1);
    }
    while (i < argc)
    {
        if (ft_atoi(argv[i]) <= 0)
        {
            error(INPUT_ERROR_2, NULL);
            return (1);
        }
        i++;
    }
    return (0);
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc < 5 || argc > 6)
        return (error(INPUT_ERROR_3, NULL));
    if (input_checker(argc, argv))
        return (1);
    if (init(&data, argv, argc))
        return (1);
    if (data.philo_num == 1)
        return (case_one(&data));
    if (thread_init(&data))
        return (1);
    ft_exit(&data);
    return (0);
}