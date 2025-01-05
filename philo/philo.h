/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jparnahy <jparnahy@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 22:13:39 by jparnahy          #+#    #+#             */
/*   Updated: 2025/01/05 01:42:46 by jparnahy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

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

typedef struct s_table 
{
    int             num_philosophers; //number of philosophers
    int             time_to_die; //time to die in ms
    int             time_to_eat; //time to eat in ms
    int             time_to_sleep; //time to sleep in ms
    int             meals_required; //number of meals required
    pthread_mutex_t *forks; //array of mutex to represente the forks
    pthread_mutex_t print_lock; //mutex to protect the print
    t_philosopher   *philosophers; //array of philosophers
    long            start_time; //timestamp of the start of the simulation
    int             stop_simulation; //flag to stop the simulation
}                   t_table;


/* MAIN FUNCTIONS */
void    free_table(t_table *table);
int     validate_args(int argc, char **argv);
int     main(int argc, char **argv);

/* INIT FUNCTIONS */
void    start_simulation(t_table *table);
int     init_table(t_table *table, int argc, char **argv);
int     init_forks(t_table *table);
int     init_mutex(pthread_mutex_t *mutex);
int     init_philosophers(t_table *table);
int     init_philosopher(t_philosopher *philo, t_table *table, int id);
int     init_philosopher_thread(t_philosopher *philo);

/* ACTION FUNCTIONS */
void    *philosopher_life(void *arg);
void    take_forks(t_philosopher *philo);
void    eat(t_philosopher *philo);
void    sleep(t_philosopher *philo);
void    think(t_philosopher *philo);

/* UTILS FUNCTIONS */
long    get_current_time(void);
long    get_time(void);
void    print_status(t_philosopher *philo, char *status);
void    print_error(char *msg);
void    ft_usleep(long time);
void    ft_sleep(long time);


/* FROM LIBFT */
int     ft_atoi(const char *nptr);



# endif
