/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 12:23:11 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/05 19:12:49 by jparnahy         ###   ########.fr       */
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
/*void    take_forks(t_philosopher *philo)
{
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(philo->right_fork);
    pthread_mutex_lock(&philo->table->print_lock);
    print_action(philo->id, "has taken a fork");
    pthread_mutex_unlock(&philo->table->print_lock);
}*/

void take_forks(t_philosopher *philo)
{
    // Pega o primeiro garfo (esquerdo)
    pthread_mutex_lock(philo->left_fork);
    pthread_mutex_lock(&philo->table->print_lock);
    print_action(philo->id, "has taken the left fork");
    pthread_mutex_unlock(&philo->table->print_lock);

    // Atualiza o tempo de última refeição ao pegar o primeiro garfo
    philo->last_meal_time = get_current_time();

    // Tenta pegar o segundo garfo (direito)
    if (pthread_mutex_trylock(philo->right_fork) != 0)
    {
        // Se não conseguir pegar o segundo garfo, libera o primeiro e sai
        pthread_mutex_unlock(philo->left_fork);
        return;
    }
    
    // Se conseguir pegar o segundo garfo
    pthread_mutex_lock(&philo->table->print_lock);
    print_action(philo->id, "has taken the forks");
    pthread_mutex_unlock(&philo->table->print_lock);
}

// Function to simulate the philosopher eating
/*void    to_eat(t_philosopher *philo)
{
    pthread_mutex_lock(&philo->table->print_lock);
    if (philo->table->stop_simulation)
    {
        pthread_mutex_unlock(&philo->table->print_lock);
        return ;
    }
    print_action(philo->id, "is eating");
    philo->last_meal_time = get_current_time();
    pthread_mutex_unlock(&philo->table->print_lock);

    usleep(philo->table->time_to_eat * 1000);
    
    pthread_mutex_lock(&philo->table->meal_lock);
    philo->meals_eaten++;
    if (philo->meals_eaten == philo->table->meals_required)
        philo->table->philosophers_done++;
    pthread_mutex_unlock(&philo->table->meal_lock);
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);

    release_forks(philo);  // Libera os garfos após comer
}*/

void to_eat(t_philosopher *philo)
{
    long start_time;
    long current_time;

    pthread_mutex_lock(&philo->table->print_lock);
    if (philo->table->stop_simulation)
    {
        pthread_mutex_unlock(&philo->table->print_lock);
        return ;
    }
    print_action(philo->id, "is eating");
    philo->last_meal_time = get_current_time();  // Atualiza ao começar a comer
    pthread_mutex_unlock(&philo->table->print_lock);

    start_time = get_current_time();
    while (1)
    {
        current_time = get_current_time();
        if ((current_time - start_time) >= philo->table->time_to_eat)
            break;

        // Atualiza periodicamente enquanto come
        philo->last_meal_time = current_time;
        usleep(500);  // Pequeno atraso para evitar sobrecarga
    }

    pthread_mutex_lock(&philo->table->meal_lock);
    philo->meals_eaten++;
    if (philo->meals_eaten == philo->table->meals_required)
        philo->table->philosophers_done++;
    pthread_mutex_unlock(&philo->table->meal_lock);

    release_forks(philo);  // Libera os garfos após comer
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