/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:51:06 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/12 17:56:44 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	case_one(t_data *data)
{
	printf("%lu %d has died\n", data->death_time, 1);
	ft_exit (data);
	return (0);
}

int	validate_args(int argc, char **argv)
{
	int	i;

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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
	{
		print_error(INPUT_ERROR_3, NULL);
		return (1);
	}
	if (validate_args(argc, argv))
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
