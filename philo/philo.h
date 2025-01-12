/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:38:57 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/12 18:09:00 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

/* LIBRARIES */
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

/* TO INPUT ERROR */
# define INPUT_ERROR_1 "Error: invalid arguments"
# define INPUT_ERROR_2 "Error: invalid characters in arguments"
# define INPUT_ERROR_3 "Error: invalid number of arguments"
# define INPUT_ERROR_4 "Error: Number of Phisopher must be lower then 200"
# define INPUT_ERROR_5 "Error: time values must be at least 60ms"

/* TO ALLOCATION ERROR  */
# define MALLOC_ERROR_1 "Error while allocating memory for threads ids"
# define MALLOC_ERROR_2 "Error while allocating forks"
# define MALLOC_ERROR_3 "Error while allocating philos"

/* TO PTHREAD ERROR */
# define PTHREAD_ERROR_THR "Error while creating thread"
# define PTHREAD_ERROR_JOIN "Error while joining thread"
# define PTHREAD_ERROR_INIT "Error while destroying mutex"

/* TO TIME ERROR */
# define TIME_ERROR "Error while getting time"

/* PHILOSOPHERS MESSANGES */
# define PHILO_EAT "is eating"
# define PHILO_SLEEP "is sleeping"
# define PHILO_THINK "is thinking"
# define PHILO_FORK "has taken a fork"
# define PHILO_RFORK "has taken a right fork"
# define PHILO_LFORK "has taken a left fork"
# define PHILO_DIED "died"

/* DATAS */
struct	s_data;

typedef struct	s_philo
{
	pthread_t	t1; 
	int		id; 
	int		eat_count; 
	int		status; 
	int		eating; 
	u_int64_t	time_to_die; 
	pthread_mutex_t	*l_fork; 
	pthread_mutex_t	*r_fork; 
	pthread_mutex_t	lock; 
	struct s_data	*data; 
}			t_philo;

typedef struct	s_data
{
	int             philo_num;
	int             meals_nb;
	int             dead;
	int             finished;
	u_int64_t       death_time;
	u_int64_t       eat_time;
	u_int64_t       sleep_time;
	u_int64_t       start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t lock;
	pthread_mutex_t write;
	pthread_t       *tid;
	t_philo         *philos;
}                   t_data;

/* UTILS */
long        ft_atoi(const char *str);
int         ft_strcmp(char *str1, char *str2);
int         print_error(char *error, t_data *data);
void        messages(char *str, t_philo *philo);
void        ft_exit(t_data *data);

/* INIT */
int         thread_init(t_data *data);
int         init(t_data *data, char **argv, int argc);

/* VALIDATE */
int         input_checker(char **argv); 

/* TIME */
u_int64_t   get_time(void);
int         ft_usleep(useconds_t time);

/* ACTIONS */
void        eat(t_philo *philo);

/* ROTINE */
void        *routine(void *philo_ptr);

#endif
