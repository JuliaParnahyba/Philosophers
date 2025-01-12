/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:51:06 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/12 19:58:01 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	case_one(t_table *table)
{
	printf("%lu %d has died\n", table->time_to_die, 1);
	exit_dinner(table);
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
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0)
		{
			print_error(INPUT_ERROR_2, NULL);
			return (1);
		}
		i++;
	}
	if (ft_atoi(argv[2]) < 60 || ft_atoi(argv[3]) < 60 || ft_atoi(argv[4]) < 60)
	{
		print_error(INPUT_ERROR_5, NULL);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6)
	{
		print_error(INPUT_ERROR_3, NULL);
		print_error(INPUT_ERROR_0, NULL);
		return (1);
	}
	if (validate_args(argc, argv))
		return (1);
	if (init(&table, argv, argc))
		return (1);
	if (table.philo_nbr == 1)
		return (case_one(&table));
	if (thread_init(&table))
		return (1);
	exit_dinner(&table);
	return (0);
}
