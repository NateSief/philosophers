/* ************************************************************************** */
/*																			  */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:19:41 by nate              #+#    #+#             */
/*   Updated: 2024/09/15 15:22:28 by nate             ###   ########.fr       */
/*																			  */
/* ************************************************************************** */


#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
/* ************************************************************************** */
/*								INCLUDES									  */
/* ************************************************************************** */
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <errno.h>
/* ************************************************************************** */
/*								 DEFINES									  */
/* ************************************************************************** */
# ifndef PHILO_MAX
#  define PHILO_MAX 200
# endif // PHILO_MAX

# ifndef DEBUG_MOD
#  define DEBUG_MOD 0
# endif // DEBUG_MOD

# ifndef COULEURS_H
#  define COULEURS_H

// Couleurs de texte
#  define RESET        "\033[0m"      // Reset
#  define BLACK        "\033[30m"     // Noir
#  define RED          "\033[31m"     // Rouge
#  define GREEN        "\033[32m"     // Vert
#  define YELLOW       "\033[33m"     // Jaune
#  define BLUE         "\033[34m"     // Bleu
#  define MAGENTA      "\033[35m"     // Magenta
#  define CYAN         "\033[36m"     // Cyan
#  define WHITE        "\033[37m"     // Blanc

// Couleurs de fond
#  define BG_BLACK     "\033[40m"     // Fond Noir
#  define BG_RED       "\033[41m"     // Fond Rouge
#  define BG_GREEN     "\033[42m"     // Fond Vert
#  define BG_YELLOW    "\033[43m"     // Fond Jaune
#  define BG_BLUE      "\033[44m"     // Fond Bleu
#  define BG_MAGENTA   "\033[45m"     // Fond Magenta
#  define BG_CYAN      "\033[46m"     // Fond Cyan
#  define BG_WHITE     "\033[47m"     // Fond Blanc

// Styles de texte
#  define BOLD         "\033[1m"      // Gras
#  define UNDERLINE    "\033[4m"      // Souligné
#  define INVERSE      "\033[7m"      // Inversé (couleur de fond et texte)

# endif /* COULEURS_H */
/* ************************************************************************** */
/*								STUCTURES									  */
/* ************************************************************************** */

typedef struct s_info t_info;

typedef struct s_mutex
{
	pthread_mutex_t	mutex;
	int				value;
} t_mutex;

typedef struct s_philo
{
	int			id;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	int			meal_num;
	long		last_meal;
	t_info		*info;
	t_mutex		*l_fork;
	t_mutex		*r_fork;
	pthread_t	thread;
} t_philo;

typedef struct s_info
{
	int			limit;
	int			nb_philo;
	int			t_die;
	int			t_eat;
	int			t_sleep;
	long		start;
	t_mutex		meals[PHILO_MAX];
	t_mutex		printf;
	t_mutex		info;
	t_mutex		is_dead;
	t_mutex		*forks;
	t_philo		*philo_tab;
} t_info;
/* ************************************************************************** */
/*								PROTOTYPES									  */
/* ************************************************************************** */

int		ft_error(int code, t_info *info);
int		ft_init(t_info *info, char **av);
int		ft_atoi(char *str);
int		ft_pars(t_info *info);
int		ft_need_stop(t_philo *philo);
int		ft_routine_eat(t_philo *philo);
int		ft_sleep(int timer, t_philo *philo);
int		monitor(t_info *info);
long	ft_get_time(t_info *info);
long	timestamp(void);
void	print_log(int state, t_philo *philo);
void	*routine(void *arg);
/* ************************************************************************** */
/*								  DEBUG 									  */
/* ************************************************************************** */


int 	my_lock(pthread_mutex_t *mutex, const char *mutex_name, const char *func, int line);
int		my_unlock(pthread_mutex_t *mutex, const char *mutex_name, const char *func, int line);

// # define pthread_mutex_lock(mutex) my_lock(mutex, #mutex, __func__, __LINE__)
// # define pthread_mutex_unlock(mutex) my_unlock(mutex, #mutex, __func__, __LINE__)

#endif