/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 12:49:40 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/10 13:52:14 by jparnahy         ###   ########.fr       */
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
# define INPUT_ERROR_1 "Error: invalid arguments\n"
# define INPUT_ERROR_2 "Error: invalid characters in arguments\n"
# define INPUT_ERROR_3 "Error: invalid number of arguments\n"
# define INPUT_ERROR_4 "Error: Number of Phisopher must be lower then 200\n"
# define INPUT_ERROR_5 "Error: time values must be at least 60ms\n"

/* TO ALLOCATION ERROR  */
# define MALLOC_ERROR_1 "Error while allocating memory for threads ids\n" //alloc_err_1
# define MALLOC_ERROR_2 "Error while allocating philos\n" //alloc_err_3
# define MALLOC_ERROR_3 "Error while allocating forks\n" //alloc_err_2

/* TO PTHREAD ERROR */
# define PTHREAD_ERROR_THR "Error while creating thread\n" //th_err
# define PTHREAD_ERROR_JOIN "Error while joining thread\n" //join_err
# define PTHREAD_ERROR_INIT "Error while destroying mutex\n" //init_err_1

/* TO TIME ERROR */
# define TIME_ERROR "Error while getting time\n" //time_err

/* PHILOSOPHERS MESSANGES */
# define PHILO_EAT "is eating\n" //eating
# define PHILO_SLEEP "is sleeping\n" //sleeping
# define PHILO_THINK "is thinking\n" //thinking
# define PHILO_RFORK "has taken a right fork\n" //take_forks
# define PHILO_LFORK "has taken a left fork\n" //take_forks
# define PHILO_DIED "died\n" //died

/* DATAS */
struct s_table;

typedef struct  s_philo
{
    pthread_t       thread; //t1
    int             id; //id
    int             count_eat; //eat_count
    int             last_meal; //status
    int             eating; //eating
    u_int64_t        the_death; //time_to_die
    pthread_mutex_t *left_fork; //l_fork
    pthread_mutex_t *right_fork; //r_fork
    pthread_mutex_t meal_lock; //lock
    struct s_table  *table; //data
}                   t_philo;

typedef struct  s_table
{
    int             nb_philo; //philo_num
    int             nb_must_eat; //meals_nb
    int             dead; //dead
    int             the_end; //finished
    u_int64_t       time_to_die; //death_time
    u_int64_t       time_to_eat; //eat_time
    u_int64_t       time_to_sleep; //sleep_time
    u_int64_t       time_to_start; //start_time
    pthread_mutex_t *forks; //forks
    pthread_mutex_t table_lock; //lock
    pthread_mutex_t print_lock; //write
    pthread_t       *threads_id; //tid
    t_philo         *philos; //philos
}                   t_table;

/* UTILS */
long        ft_atoi(const char *str);
int         ft_strcmp(char *str1, char *str2);
int         print_error(char *str, t_table *table); //error
void        print_status(t_philo *philo, char *message); //messager

/* INIT */
int         start_simulation(t_table *table); //thread_init
int         init_dnr(t_table *table, int argc, char **argv); //init
int         init_philos(t_table *table);
int         init_forks(t_table *table);
int         init_mutex(t_table *table);

/* VALIDATE */
int         validate_args(int argc, char **argv); //input_checker

/* SPECIAL CASE */
void         one_philo(t_table *table);

/* TIME */
u_int64_t   get_time(void);
int         ft_usleep(useconds_t time);

/* ROUTINE */
void        *philo_life(void *table_ptr);
void        *maitre(void *philo_ptr);
void        *the_routine(void *philo_ptr);

/* ACTIONS */
void        take_forks(t_philo *philo);
void        to_sleep(t_philo *philo);
void        to_eat(t_philo *philo); //eat

/* DESTROY */
void        destroy_table(t_table *table); //ft_exit
void        free_table(t_table *table); 


#endif
