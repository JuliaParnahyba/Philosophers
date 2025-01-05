/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:13:39 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/05 18:18:32 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

/* TO REPRESENTING THE PHILOSOPHERS*/
typedef struct s_philosopher 
{
    int             id; //number of philosopher
    pthread_t       thread; //thread of philosopher
    pthread_mutex_t *left_fork; //Mutex to represente the left fork
    pthread_mutex_t *right_fork; //Mutex to represente the right fork
    long            last_meal_time; //timestamp of the last meal
    int             meals_eaten; //number of meals eaten
    struct s_table  *table; //pointer to the table
}                   t_philosopher;

/* TO CHECK FORKS */
typedef struct s_fork
{
    pthread_mutex_t fork; //mutex to represent the fork
    int             in_use;  // 1 = ocupado, 0 = livre
}                   t_fork;


/* TO REPRESENTING THE TABLE */
typedef struct s_table 
{
    int             num_philosophers; //number of philosophers
    int             time_to_die; //time to die in ms
    int             time_to_eat; //time to eat in ms
    int             time_to_sleep; //time to sleep in ms
    int             meals_required; //number of meals required
    int             philosophers_done; //number of philosophers that have eaten the required number of meals
    int             stop_simulation; //flag to stop the simulation
    long            start_time; //timestamp of the start of the simulation
    t_fork          *forks_locks; //array of forks
    pthread_mutex_t *forks; //array of mutexes to protect the forks
    pthread_mutex_t meal_lock; //mutex to protect the meals_required
    pthread_mutex_t print_lock; //mutex to protect the print
    t_philosopher   *philosophers; //array of philosophers    
}                   t_table;

/* THE ALL FUNCTIONS */
/* MAIN */
void    free_table(t_table *table);
int     validate_args(int argc, char **argv);
int     main(int argc, char **argv);

/* INIT */
int     init_table(t_table *table, int argc, char **argv);
void    start_simulation(t_table *table);
void    *monitor_life(void *arg);

/* ACTION */
void    *philosopher_life(void *arg);
void    take_forks(t_philosopher *philo);
void    to_eat(t_philosopher *philo);
void    to_sleep(t_philosopher *philo);
void    to_think(t_philosopher *philo);

/* UTILS */
long    get_current_time(void);
void    print_action(int id, const char *action);
void    release_forks(t_philosopher *philo);

/* FROM LIBFT */
int     ft_atoi(const char *nptr);

# endif
