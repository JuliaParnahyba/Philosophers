/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/10 15:38:57 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/13 14:22:36 by jparnahy         ###   ########.fr       */
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
# define RESET "\033[0m"
# define RED "\033[0;31m"
# define ITALIC_RED "\033[3;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define ITALIC_YELLOW "\033[3;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"

/* TEXT EFFECTS */
# define BOLD "\033[1m"
# define UNDERLINE "\033[4m"
# define ITALIC "\033[3m"

/* EMOJIS */
# define EMOJI_ERROR "❌"
# define EMOJI_CHECK "✅😋"
# define EMOJI_WARNING "⚠️"
# define EMOJI_FOOD " 🍝"
# define EMOJI_FORK " 🍴"
# define EMOJI_SLEEP " 😴"
# define EMOJI_THINK " 🧐"
# define EMOJI_SKULL "⚰️ 🪦 💀"

/* TO INPUT ERROR */
# define INPUT_ERROR_0 EMOJI_WARNING ITALIC" The args must be:\n" \
ITALIC_YELLOW"./philo <nbr_of_philos> <time_to_die> <time_to_eat> \
<time_to_sleep> [nbr_of_times_must_eat]\n"RESET
# define INPUT_ERROR_1 EMOJI_ERROR ITALIC_RED" \
Error: invalid arguments\n"RESET
# define INPUT_ERROR_2 EMOJI_ERROR ITALIC_RED" \
Error: invalid characters in arguments\n"RESET
# define INPUT_ERROR_3 EMOJI_ERROR ITALIC_RED" \
Error: invalid number of arguments\n"RESET
# define INPUT_ERROR_4 EMOJI_WARNING ITALIC_YELLOW" \
Error: number of Phisopher must be lower then 200\n"RESET
# define INPUT_ERROR_5 EMOJI_WARNING ITALIC_YELLOW" \
Error: time values must be at least 60ms\n"RESET

/* TO ALLOCATION ERROR  */
# define MALLOC_ERROR_1 EMOJI_ERROR ITALIC_RED" \
Error while allocating memory for threads ids"RESET
# define MALLOC_ERROR_2 EMOJI_ERROR ITALIC_RED" \
Error while allocating forks"RESET
# define MALLOC_ERROR_3 EMOJI_ERROR ITALIC_RED" \
Error while allocating philos"RESET

/* TO PTHREAD ERROR */
# define PTHREAD_ERROR_THR EMOJI_ERROR EMOJI_ERROR ITALIC_RED" \
Error while creating thread"RESET
# define PTHREAD_ERROR_JOIN EMOJI_ERROR EMOJI_ERROR ITALIC_RED" \
Error while joining thread"RESET
# define PTHREAD_ERROR_INIT EMOJI_ERROR EMOJI_ERROR ITALIC_RED" \
Error while destroying mutex"RESET

/* TO TIME ERROR */
# define TIME_ERROR EMOJI_ERROR ITALIC_RED" \
Error while getting time"RESET

/* PHILOSOPHERS MESSANGES */
# define PHILO_EAT "is eating"EMOJI_FOOD
# define PHILO_SLEEP "is sleeping"EMOJI_SLEEP
# define PHILO_THINK "is thinking"EMOJI_THINK
# define PHILO_FORK "has taken a fork"EMOJI_FORK
# define PHILO_RFORK "has taken a right fork"EMOJI_FORK
# define PHILO_LFORK "has taken a left fork"EMOJI_FORK
# define PHILO_DIED "died\n"EMOJI_SKULL
# define PHILO_FINISHED RESET YELLOW "\nhas finished eating "EMOJI_CHECK

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
void        print_status(char *status, t_philo *philo, char *color);
void        exit_dinner(t_table *table);
int			ft_isalpha(int c);

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
