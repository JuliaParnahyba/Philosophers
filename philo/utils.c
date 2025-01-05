/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:24:14 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/05 18:28:05 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Get the current time in milliseconds
long    get_current_time(void) 
{
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// Print the action of a philosopher
void    print_action(int id, const char *action) 
{
    printf("%ld %d %s\n", get_current_time(), id, action);
}

void release_forks(t_philosopher *philo)
{
    // Libera o garfo esquerdo
    pthread_mutex_unlock(philo->left_fork);
    
    // Libera o garfo direito
    pthread_mutex_unlock(philo->right_fork);
}


