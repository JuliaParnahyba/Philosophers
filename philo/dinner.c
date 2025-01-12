/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 17:03:20 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/12 20:05:38 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (print_error("gettimeofday() FAILURE\n", NULL));
	return ((tv.tv_sec * (u_int64_t)1000) + (tv.tv_usec / 1000));
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	print_status(PHILO_FORK, philo);
	pthread_mutex_lock(philo->left_fork);
	print_status(PHILO_FORK, philo);
}

void	sleeping(t_philo *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	print_status(PHILO_SLEEP, philo);
	ft_usleep(philo->table->time_to_sleep);
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	pthread_mutex_lock(&philo->lock);
	philo->eating = 1;
	philo->the_death_time = get_time() + philo->table->time_to_die;
	print_status(PHILO_EAT, philo);
	philo->eat_count++;
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(philo->table->time_to_eat);
	philo->eating = 0;
	sleeping(philo);
}
