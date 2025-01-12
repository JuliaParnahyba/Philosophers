/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:38:57 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/12 20:06:18 by jparnahy         ###   ########.fr       */
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

/* COLORS */
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"

/* TO INPUT ERROR */
# define INPUT_ERROR_0 "The args must be:\n./philo <nbr_of_philos> \
<time_to_die> <time_to_eat> <time_to_sleep> [nbr_of_times_must_eat]"
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
struct	s_table;

typedef struct	s_philo
{
	pthread_t		philo_thr_id;
	int				philo_id;
	int				eat_count;
	int				status;
	int				eating;
	u_int64_t		the_death_time;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork; 
	pthread_mutex_t	lock;
	struct s_table	*table;
}					t_philo;

typedef struct	s_table
{
	int             philo_nbr;
	int             max_meals;
	int             dead;
	int             finished;
	u_int64_t       time_to_die;
	u_int64_t       time_to_eat;
	u_int64_t       time_to_sleep;
	u_int64_t       start_time;
	pthread_mutex_t *forks;
	pthread_mutex_t lock;
	pthread_mutex_t write;
	pthread_t       *tid;
	t_philo         *philos;
}                   t_table;

/* UTILS */
long        ft_atoi(const char *str);
int         ft_strcmp(char *str1, char *str2);
int         print_error(char *error, t_table *table);
void        print_status(char *status, t_philo *philo);
void        exit_dinner(t_table *table);

/* INIT */
int         thread_init(t_table *table);
int         init(t_table *table, char **argv, int argc);

/* VALIDATE */
int			validate_args(int argc, char **argv);

/* TIME */
u_int64_t   get_time(void);
int         ft_usleep(useconds_t time);

/* ACTIONS */
void        eating(t_philo *philo);

/* ROTINE */
void        *dinner_party(void *philo_ptr);

#endif
