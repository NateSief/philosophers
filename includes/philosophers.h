/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:31:45 by nate              #+#    #+#             */
/*   Updated: 2024/08/25 08:31:02 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ************************************************************************** */
/*									DEFINES									  */
/* ************************************************************************** */

# define CREATE_THREAD pthread_create(&info->philo_tab[i].thread, NULL, \
		(void *)routine, (void *)(&info->philo_tab[i]));
# define NUM_PHILO info->philo_num

/* ************************************************************************** */

/* ************************************************************************** */
/*									INCLUDES								  */
/* ************************************************************************** */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <errno.h>
/* ************************************************************************** */

/* ************************************************************************** */
/*									STRUCTURES								  */
/* ************************************************************************** */

typedef struct s_philo t_philo;

//	Allow me to know if my mutex has been initialized or not, and then don't
//		try to destroy an uninitialized mutex
typedef struct s_mutex
{
	pthread_mutex_t	*mutex;
	char			init;
	int				value;
} t_mutex;

//	Stock of all the information of the program :
//		- limit = is there a number of meal that stop the simulation ?
//		- philo_num = number of philosophers in the simulation
//		- t_die = time when the philo die if he hasn't eat
//		- t_eat = time he takes to eat
//		- t_sleep = time he takes to sleep
//		- start = timer of the beggining of the simulation
//		- printf = mutex to lock the printd and don't have mixed printf output
//		- philo_tab = tab of all the philosophers I have
typedef struct s_info
{
	int					dead_philo;
	int					limit;
	int					philo_num;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	struct timeval		*start;
	t_mutex				is_dead;
	t_mutex				printf;
	t_philo				*philo_tab;
} t_info;

// Stock of all the informations of each philosopher
//		- index = id of the philo in the simulation
//		- meal_num = number of meals the philosopher has eat during the simu
//		- t_die = time after a meal where a philo will die
//		- t_eat = time a philo will take to eat
//		- t_sleep = time a philo will take to sleep
//		- last_meal = timer of his last meal
//		- thread = contain a pointer on the thread
//		- is_dead = if the philo is dead, it goes to one via a monitor action
//		- r_fork = his fork
//		- l_fork = the fork of his neigbour
typedef struct s_philo
{
	int			index;
	int			meal_num;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	long		last_meal;
	pthread_t	thread;
	t_info		*info;
	t_mutex		r_fork;
	t_mutex		*l_fork;
} t_philo;
/* ************************************************************************** */

/* ************************************************************************** */
/*									PROTOTYPES								  */
/* ************************************************************************** */
/* main.c 		*/

/*	ft_init.c	*/

int		ft_init(t_info *info);
/*	ft_pars.c	*/

int		ft_pars(char **av, t_info *info);
/* ft_error.c 	*/

int		ft_error(int error_code, t_info *info);
/*	routine.c	*/

void	*routine(void *arg);
int		ft_need_stop(t_philo *philo);
/*	monitor.c	*/

int		monitor(t_info *info);
/*	monitor.c	*/

long	ft_convert(struct timeval *to_convert);
long	ft_time(t_info *info);
/*	utils.c		*/

void	print_log(int state_value, t_philo *philo);
int		ft_sleep(t_philo *philo, int value);
long	ft_time(t_info *info);
long	ft_convert(struct timeval *to_convert);
int		ft_atoi(char *str);
/*	ft_eat.c	*/

void	routine_eat(t_philo *philo);

/* ************************************************************************** */

/* ************************************************************************** */
/*									DEBUG SHIT								  */
/* ************************************************************************** */


int my_pthread_mutex_lock(pthread_mutex_t *mutex, const char *mutex_name, const char *func, int line);
int my_pthread_mutex_unlock(pthread_mutex_t *mutex, const char *mutex_name, const char *func, int line);

// # define pthread_mutex_lock(mutex) my_pthread_mutex_lock(mutex, #mutex, __FUNCTION__, __LINE__)
// # define pthread_mutex_unlock(mutex) my_pthread_mutex_unlock(mutex, #mutex, __FUNCTION__, __LINE__)

#endif