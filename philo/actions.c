/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:23:11 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/05 13:59:49 by jparnahy         ###   ########.fr       */
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
    print_action(philo->id, "is eating");
    philo->last_meal_time = get_current_time();
    philo->meals_eaten++;
    pthread_mutex_unlock(&philo->table->print_lock);

    usleep(philo->table->time_to_eat * 1000);

    if (philo->meals_eaten == philo->table->meals_required)
    {
        pthread_mutex_lock(&philo->table->meal_lock);
        philo->table->philosophers_done++;
        if (philo->table->philosophers_done == philo->table->num_philosophers)
            philo->table->stop_simulation = 1;  // Interrompe imediatamente
        pthread_mutex_unlock(&philo->table->meal_lock);
    }

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
        to_think(philo);
        take_forks(philo);
        to_eat(philo);
        to_sleep(philo);
    }
    return (NULL);
}