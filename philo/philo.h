/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:49:40 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/09 15:08:46 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/time.h>

/* TO ALLOCATION ERROR  */
# define MALLOC_ERROR_1 "error while allocating memory for threads ids\n"
# define MALLOC_ERROR_2 "error while allocating philos\n"
# define MALLOC_ERROR_3 "error while allocating forks\n"

/* TO PTHREAD ERROR */
# define PTHREAD_ERROR_THR "error while creating thread\n"
# define PTHREAD_ERROR_JOIN "error while joining thread\n"
# define PTHREAD_ERROR_INIT "error while destroying mutex\n"

/* TO INPUT ERROR */
# define INPUT_ERROR_1 "invalid input chars\n"
# define INPUT_ERROR_2 "invalid input values\n"

/* TO TIME ERROR */
# define TIME_ERROR "error while getting time\n"

/* PHILOSOPHERS MESSANGES */
# define PHILO_EAT "is eating\n"
# define PHILO_SLEEP "is sleeping\n"
# define PHILO_THINK "is thinking\n"
# define PHILO_FORK "has taken a fork\n"
# define PHILO_DIED "died\n"

/* DATAS */
struct s_table;

typedef struct  s_philo
{
    pthread_t       thread;
    int             id;
    int             count_eat;
    int             last_meal;
    int             eating;
    u_int64_t        the_death;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
    pthread_mutex_t meal_lock;
    struct s_table  *table;
}                   t_philo;

typedef struct  s_table
{
    int             nb_philo;
    int             nb_must_eat;
    int             dead;
    int             the_end;
    u_int64_t       time_to_die;
    u_int64_t       time_to_eat;
    u_int64_t       time_to_sleep;
    u_int64_t       time_to_start;
    pthread_mutex_t *forks;
    pthread_mutex_t print_lock;
    pthread_mutex_t write_lock;
    pthread_t       *threads;
    t_philo         *philos;
}                   t_table;

/* UTILS */
long        ft_atoi(const char *str);
int         ft_strcmp(char *str1, char *str2);
int         print_error(char *str, t_table *table);
void        print_status(t_philo *philo, char *message);

/* INIT */
int         start_simulation(t_table *table);
int         init(t_table *table, int argc, char **argv);
int         init_philos(t_table *table);

/* THREADS */
void        *philo_life(void *philo_ptr);

/* TIME */
u_int64_t   get_time(void);
int         ft_usleep(useconds_t time);

/* ROUTINE */
void    *philo_life(void *table_ptr);
void    *maitre(void *philo_ptr);
void    *the_routine(void *philo_ptr);

/* ACTIONS */
void        take_forks(t_philo *philo);
void        to_sleep(t_philo *philo);
void        to_eat(t_philo *philo);

/* DESTROY */
void        destroy_table(t_table *table);
void        free_table(t_table *table);


#endif
