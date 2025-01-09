/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:45:52 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/09 14:52:40 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

u_int64_t   get_time(void)
{
    struct timeval  tv;
    u_int64_t       time;

    if (gettimeofday(&tv, NULL))
        print_error(TIME_ERROR, NULL);
    time = tv.tv_sec * 1000;
    time += tv.tv_usec / 1000;
    return (time);
}

int ft_usleep(useconds_t time)
{
    u_int64_t start;

    start = get_time();
    while (get_time() - start < time)
        usleep(time / 10);
    return (0);
}

int	ft_strcmp(char *str, char *value)
{
	int	i;

	i = 0;
	while (str[i] == value[i] && str[i] && value[i])
		i++;
	if (value[i] == '\0' && str[i] == '\0')
	{
		return (0);
	}
	else
	{
		return (1);
	}
}

long    ft_atoi(const char *nptr)
{
	int	i;
	int	nbr;
	int	sign;

	i = 0;
	nbr = 0;
	sign = 1;
	if (nptr[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nbr = nbr * 10 + nptr[i] - '0';
		i++;
	}
	return (nbr * sign);
}
