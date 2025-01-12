/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:05:39 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/12 19:47:00 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	allocation(t_table *table)
{
	table->tid = malloc(sizeof(pthread_t) * table->philo_nbr);
	if (!table->tid)
		return (print_error(MALLOC_ERROR_1, table));
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_nbr);
	if (!table->forks)
		return (print_error(MALLOC_ERROR_2, table));
	table->philos = malloc(sizeof(t_philo) * table->philo_nbr);
	if (!table->philos)
		return (print_error(MALLOC_ERROR_3, table));
	return (0);
}

int	init_forks(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
		pthread_mutex_init(&table->forks[i], NULL);
	i = 0;
	table->philos[0].left_fork = &table->forks[0];
	table->philos[0].right_fork = &table->forks[table->philo_nbr - 1];
	i = 1;
	while (i < table->philo_nbr)
	{
		table->philos[i].left_fork = &table->forks[i];
		table->philos[i].right_fork = &table->forks[i - 1];
		i++;
	}
	return (0);
}

void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_nbr)
	{
		table->philos[i].table = table;
		table->philos[i].philo_id = i + 1;
		table->philos[i].the_death_time = table->time_to_die;
		table->philos[i].eat_count = 0;
		table->philos[i].eating = 0;
		table->philos[i].status = 0;
		pthread_mutex_init(&table->philos[i].lock, NULL);
		i++;
	}
}

int	init_table(t_table *table, char **argv, int argc)
{
	table->philo_nbr = (int) ft_atoi(argv[1]);
	table->time_to_die = (u_int64_t) ft_atoi(argv[2]);
	table->time_to_eat = (u_int64_t) ft_atoi(argv[3]);
	table->time_to_sleep = (u_int64_t) ft_atoi(argv[4]);
	if (argc == 6)
		table->max_meals = (int) ft_atoi(argv[5]);
	else
		table->max_meals = -1;
	if (table->philo_nbr <= 0 || table->philo_nbr > 200 || table->time_to_die < 60
		|| table->time_to_eat < 60 || table->time_to_sleep < 60)
		return (print_error(INPUT_ERROR_1, NULL));
	table->dead = 0;
	table->finished = 0;
	pthread_mutex_init(&table->write, NULL);
	pthread_mutex_init(&table->lock, NULL);
	return (0);
}

int	init(t_table *table, char **argv, int argc)
{
	if (init_table(table, argv, argc))
		return (1);
	if (allocation(table))
		return (1);
	if (init_forks(table))
		return (1);
	init_philos(table);
	return (0);
}
