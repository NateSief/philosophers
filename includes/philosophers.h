/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:31:45 by nate              #+#    #+#             */
/*   Updated: 2024/08/09 14:06:02 by nate             ###   ########.fr       */
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
# include "stdio.h"
# include "stdlib.h"
# include "unistd.h"
# include "sys/time.h"
# include "pthread.h"
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
	t_philo			*philo_tab;
	int				nb_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	char			limit;
	char			started;
	int				isddead;
	int				all_eaten;
	t_mutex			printf;
	t_mutex			simu_start;
	struct timeval	start;
} t_info;

typedef struct s_philo
{
	pthread_t		*thread;
	int				index;
	int				num_meal;
	t_mutex			r_fork;
	t_mutex			l_fork;
	long			meal;
	t_info			*info;
} t_philo;
/* ************************************************************************** */

/* ************************************************************************** */
/*									PROTOTYPES								  */
/* ************************************************************************** */
/* main.c 		*/

/* error.c		*/

void	ft_error(int error_code, t_info *infos);
/* utils.c		*/

int		ft_atoi(char *str);
long	ft_time(t_info *info);
long	convert_time(struct timeval *timestamp);
int		print_log(t_philo *philo, int state);
/* init.c		*/

void	init_philo(t_info *info);
/* pars.c		*/

void	ft_pars(char **av, t_info *info);
/* routine.c	*/

void	*routine(void *arg);
/* monitor.c	*/

void	monitor(t_info *info);
/* ************************************************************************** */

#endif