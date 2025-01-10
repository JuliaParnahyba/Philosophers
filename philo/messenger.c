/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messenger.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 14:19:06 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/10 15:34:30 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int print_error(char *error, t_table *table)
{
    printf("%s", error);
    if (table)
        destroy_table(table);
    return (1);
}

void print_status(t_philo *philo, char *message)
{
    u_int64_t time;

    pthread_mutex_lock(&philo->table->print_lock);
    time = get_time() - philo->table->time_to_start;
    if (ft_strcmp(PHILO_DIED, message) == 0 && philo->table->dead == 0)
    {
        printf("%lu %d %s", time, philo->id, message);
        philo->table->dead = 1;
    }
    else if (philo->table->dead)
        printf("%lu %d %s", time, philo->id, message);
    pthread_mutex_unlock(&philo->table->print_lock);
}