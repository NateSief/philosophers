/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:31:45 by nate              #+#    #+#             */
/*   Updated: 2024/08/12 13:44:55 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

/* ************************************************************************** */
/*									DEFINES									  */
/* ************************************************************************** */

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
} t_mutex;

//	Stock of all the information of the program :
//		- The tab of philosophers
//		- Timers (Die - Eat - Sleep)
//		- The limit of meals (-1 if there is no limit)
//		- Mutexs (Printf - Starter)
//		- Timestamp of the start of the simulation
//		-
typedef struct s_info
{
	char			limit;
	char			started;
	int				all_eaten;
	int				isddead;
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	t_mutex			printf;
	t_mutex			simu_start;
	t_mutex			info;
	t_philo			*philo_tab;
	struct timeval	start;
} t_info;

typedef struct s_philo
{
	int				index;
	int				num_meal;
	long			meal;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	pthread_t		*thread;
	t_info			*info;
	t_mutex			l_fork;
	t_mutex			r_fork;
} t_philo;
/* ************************************************************************** */

/* ************************************************************************** */
/*									PROTOTYPES								  */
/* ************************************************************************** */
/* main.c 		*/

/* error.c		*/

int		ft_error(int error_code, t_info *infos);
/* utils.c		*/

int		ft_atoi(char *str);
long	ft_time(t_info *info);
long	convert_time(struct timeval *timestamp);
int		print_log(t_philo *philo, int state);
/* init.c		*/

int	init_philo(t_info *info);
/* pars.c		*/

int		ft_pars(char **av, t_info *info);
/* routine.c	*/

int		ft_sleep(int timer, t_philo *philo);
void	lock_forks(t_philo *philo);
void	unlock_forks(t_philo *philo);
void	*routine(void *arg);
/* routine2.c	*/

int		routine_2(t_philo *philo);
/* monitor.c	*/

int	monitor(t_info *info);
/* ************************************************************************** */

/* ************************************************************************** */
/*									DEBUG SHIT								  */
/* ************************************************************************** */


int my_pthread_mutex_lock(pthread_mutex_t *mutex, const char *mutex_name, const char *func, int line);
int my_pthread_mutex_unlock(pthread_mutex_t *mutex, const char *mutex_name, const char *func, int line);

// # define pthread_mutex_lock(mutex) my_pthread_mutex_lock(mutex, #mutex, __FUNCTION__, __LINE__)
// # define pthread_mutex_unlock(mutex) my_pthread_mutex_unlock(mutex, #mutex, __FUNCTION__, __LINE__)

#endif