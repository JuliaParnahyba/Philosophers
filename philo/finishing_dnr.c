/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finishing_dnr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:30:11 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/12 19:47:33 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_table(t_table	*table)
{
	if (table->tid)
		free(table->tid);
	if (table->forks)
		free(table->forks);
	if (table->philos)
		free(table->philos);
}

void	exit_dinner(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->philo_nbr)
	{
		pthread_mutex_destroy(&table->forks[i]);
		pthread_mutex_destroy(&table->philos[i].lock);
	}
	pthread_mutex_destroy(&table->write);
	pthread_mutex_destroy(&table->lock);
	free_table(table);
}
