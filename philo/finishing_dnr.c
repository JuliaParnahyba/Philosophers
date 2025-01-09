/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finishing_dnr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:11:41 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/09 14:50:01 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    free_table(t_table *table)
{
    if (table->philos)
        free(table->philos);
    if (table->forks)
        free(table->forks);
    if (table->threads)
        free(table->threads);
}

void    destroy_table(t_table *table)
{
    int i;

    i = 0;
    while (i < table->nb_philo)
    {
        pthread_mutex_destroy(&table->forks[i]);
        pthread_mutex_destroy(&table->philos[i].meal_lock);
        i++;
    }
    pthread_mutex_destroy(&table->print_lock);
    pthread_mutex_destroy(&table->write_lock);
    free_table(table);
}