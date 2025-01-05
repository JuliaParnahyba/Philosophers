/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:23:11 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/05 15:18:46 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Function to simulate the philosopher thinking
void    to_think(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->table->print_lock);
    print_action(philo->id, "is thinking");
    pthread_mutex_unlock(&philo->table->print_lock);
}

// Function to simulate the philosopher taking a fork
void    take_forks(t_philosopher *philo)
{
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(&philo->table->print_lock);
    print_action(philo->id, "has taken a fork");
    pthread_mutex_unlock(&philo->table->print_lock);
}

// Function to simulate the philosopher eating
void    to_eat(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->table->print_lock);
    if (philo->table->stop_simulation)
    {
        pthread_mutex_unlock(&philo->table->print_lock);
        return ;
    }
    philo->last_meal_time = get_current_time();
    print_action(philo->id, "is eating");
    pthread_mutex_unlock(&philo->table->print_lock);
    usleep(philo->table->time_to_eat * 1000);
    pthread_mutex_lock(&philo->table->meal_lock);
    philo->meals_eaten++;
    if (philo->meals_eaten == philo->table->meals_required)
        philo->table->philosophers_done++;
    pthread_mutex_unlock(&philo->table->meal_lock);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

// Function to simulate the philosopher sleeping
void    to_sleep(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->table->print_lock);
    if (philo->table->stop_simulation)
    {
        pthread_mutex_unlock(&philo->table->print_lock);
        return ;
    }
    print_action(philo->id, "is sleeping");
    pthread_mutex_unlock(&philo->table->print_lock);
    usleep(philo->table->time_to_sleep * 1000);
}

// Function to simulate the philosopher living
void    *philosopher_life(void *arg)
{
    t_philosopher   *philo;

    philo = (t_philosopher *)arg;
    while (!philo->table->stop_simulation)
    {
        take_forks(philo);
        to_eat(philo);
        to_sleep(philo);
        to_think(philo);
    }
    return (NULL);
}