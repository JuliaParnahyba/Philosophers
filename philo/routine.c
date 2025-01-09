/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:57:21 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/09 19:08:30 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *philo_life(void *table_ptr)
{
    t_philo *philo;

    philo = (t_philo *)table_ptr;
    pthread_mutex_lock(&philo->table->write_lock);
    printf("time: %d", philo->table->dead);
    pthread_mutex_unlock(&philo->table->write_lock);
    while (philo->table->dead == 0)
    {
        pthread_mutex_lock(&philo->meal_lock);
        if (philo->table->the_end == philo->table->nb_philo)
            philo->table->dead = 1;
        pthread_mutex_unlock(&philo->meal_lock);
    }
    return ((void *)0);
}

void    *maitre(void *philo_ptr)
{
    t_philo *philo;

    philo = (t_philo *)philo_ptr;
    while (philo->table->dead == 0)
    {
        pthread_mutex_lock(&philo->meal_lock);
        if (get_time() >= philo->the_death && philo->eating == 0)
            print_status(philo, PHILO_DIED);
        if (philo->count_eat == philo->table->nb_must_eat)
        {
            pthread_mutex_lock(&philo->table->print_lock);
            philo->table->the_end++;
            philo->count_eat++;
            pthread_mutex_unlock(&philo->table->print_lock);
        }
        pthread_mutex_unlock(&philo->meal_lock);
    }
    return ((void *)0);
}

void    *the_routine(void *philo_ptr)
{
    t_philo *philo;

    philo = (t_philo *)philo_ptr;
    philo->the_death = philo->table->time_to_die + get_time();
    if (pthread_create(&philo->thread, NULL, &maitre, (void *)philo))
        return ((void *)1);
    while (philo->table->dead == 0)
    {
        to_eat(philo);
        print_status(philo, PHILO_SLEEP);
    }
    if (pthread_join(philo->thread, NULL))
        return ((void *)1);
    return ((void *)0);
}
