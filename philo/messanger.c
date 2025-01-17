/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messanger.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 18:28:23 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/13 14:16:58 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_error(char *error, t_table *table)
{
	printf("%s\n", error);
	if (table)
		exit_dinner(table);
	return (1);
}

void	print_status(char *status, t_philo *philo, char *color)
{
	u_int64_t	time;

	pthread_mutex_lock(&philo->table->write);
	time = get_time() - philo->table->start_time;
	if (ft_strcmp(PHILO_DIED, status) == 0 && philo->table->dead == 0)
	{
		printf("%s%lu %d %s\n", color, time, philo->philo_id, status);
		philo->table->dead = 1;
	}
	if (!philo->table->dead)
		printf("%s%lu %d %s\n", color, time, philo->philo_id, status);
	pthread_mutex_unlock(&philo->table->write);
}
