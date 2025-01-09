/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:16:10 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/09 14:25:33 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    take_forks(t_philo *philo)
{
    pthread_mutex_lock(philo->left_fork);
    print_status(philo, PHILO_FORK);
    pthread_mutex_lock(philo->right_fork);
    print_status(philo, PHILO_FORK);
}

void    to_sleep(t_philo *philo)
{
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
    print_status(philo, PHILO_SLEEP);
    ft_usleep(philo->table->time_to_sleep);
}

void    to_eat(t_philo *philo)
{
    take_forks(philo);
    pthread_mutex_lock(&philo->meal_lock);
    philo->eating = 1;
    philo->the_death = get_time() + philo->table->time_to_die;
    print_status(philo, PHILO_EAT);
    philo->count_eat++;
    ft_usleep(philo->table->time_to_eat);
    philo->eating = 0;
    pthread_mutex_unlock(&philo->meal_lock);
    to_sleep(philo);
}