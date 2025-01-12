/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 16:22:51 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/12 20:15:47 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*maitre(void *table_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) table_pointer;
	while (philo->table->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (philo->table->finished >= philo->table->philo_nbr)
			philo->table->dead = 1;
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*host(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	while (philo->table->dead == 0)
	{
		pthread_mutex_lock(&philo->lock);
		if (get_time() >= philo->the_death_time && philo->eating == 0)
			print_status(PHILO_DIED, philo);
		if (philo->eat_count == philo->table->max_meals)
		{
			pthread_mutex_lock(&philo->table->lock);
			philo->table->finished++;
			philo->eat_count++;
			pthread_mutex_unlock(&philo->table->lock);
		}
		pthread_mutex_unlock(&philo->lock);
	}
	return ((void *)0);
}

void	*dinner_party(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) philo_pointer;
	philo->the_death_time = philo->table->time_to_die + get_time();
	if (pthread_create(&philo->philo_thr_id, NULL, &host, (void *)philo))
		return ((void *)1);
	while (philo->table->dead == 0)
	{
		eating(philo);
		print_status(PHILO_THINK, philo);
	}
	if (pthread_join(philo->philo_thr_id, NULL))
		return ((void *)1);
	return ((void *)0);
}

int	thread_init(t_table *table)
{
	int			i;
	pthread_t	t0;

	i = -1;
	table->start_time = get_time();
	if (table->max_meals > 0)
	{
		if (pthread_create(&t0, NULL, &maitre, &table->philos[0]))
			return (print_error(PTHREAD_ERROR_THR, table));
	}
	while (++i < table->philo_nbr)
	{
		if (pthread_create(&table->tid[i], NULL, &dinner_party, &table->philos[i]))
			return (print_error(PTHREAD_ERROR_THR, table));
		ft_usleep(1);
	}
	i = -1;
	while (++i < table->philo_nbr)
	{
		if (pthread_join(table->tid[i], NULL))
			return (print_error(PTHREAD_ERROR_JOIN, table));
	}
	return (0);
}
