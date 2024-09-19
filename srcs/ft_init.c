/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:44:15 by nate              #+#    #+#             */
/*   Updated: 2024/09/19 13:06:54 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	While loop that init the forks mutexes
static int	init_forks(t_info *info)
{
	int	i;

	i = -1;
	while (++i < PHILO_MAX)
	{
		if (pthread_mutex_init(&info->forks[i].mutex, NULL) == -1)
			return (1);
		if (pthread_mutex_init(&info->meals[i].mutex, NULL) == -1)
			return (1);
	}
	return (0);
}

//	While loop that init the philo informations
static int	init_philos(t_info *info)
{
	int	i;

	i = -1;
	while (++i < PHILO_MAX)
	{
		if (i == 0)
			info->philo_tab[i].l_fork = &info->forks[info->nb_philo];
		else
			info->philo_tab[i].l_fork = &info->forks[i - 1];
		info->philo_tab[i].r_fork = &info->forks[i];
		info->philo_tab[i].id = i;
		info->philo_tab[i].info = info;
		info->philo_tab[i].last_meal = 0;
		info->philo_tab[i].meal_num = 0;
		info->philo_tab[i].t_die = info->t_die;
		info->philo_tab[i].t_eat = info->t_eat;
		info->philo_tab[i].t_sleep = info->t_eat;
		info->meals[i].value = 0;
	}
	return (0);
}

//	Init all the informations, the mutexes and the timeval struct
int	ft_init(t_info *info, char **av)
{
	info->nb_philo = ft_atoi(av[1]);
	info->t_die = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	info->limit = -2;
	if (av[5])
		info->limit = ft_atoi(av[5]);
	info->info.value = 0;
	if (pthread_mutex_init(&info->printf.mutex, NULL) == -1)
		return (ft_error(3, info));
	else
		info->printf.value = 0;
	if (pthread_mutex_init(&info->info.mutex, NULL) == -1)
		return (ft_error(3, info));
	else
		info->info.value = 0;
	if (pthread_mutex_init(&info->is_dead.mutex, NULL) == -1)
		return (ft_error(3, info));
	else
		info->is_dead.value = -1;
	if (init_forks(info) || init_philos(info))
		return (ft_error(3, info));
	return (0);
}
