/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:32:14 by nate              #+#    #+#             */
/*   Updated: 2024/08/25 08:22:59 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_give_forks(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
	{
		if (i == 0)
			info->philo_tab[i].l_fork = &info->philo_tab[NUM_PHILO - 1].r_fork;
		else
			info->philo_tab[i].l_fork = &info->philo_tab[i - 1].r_fork;
		info->philo_tab[i].t_die = info->t_die;
		info->philo_tab[i].t_eat = info->t_eat;
		info->philo_tab[i].t_sleep = info->t_sleep;
	}
	return (0);
}

int	ft_init_forks(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
	{
		info->philo_tab[i].r_fork.mutex = malloc(sizeof(pthread_mutex_t));
		if (!info->philo_tab[i].r_fork.mutex)
			return(ft_error(4, info));
		if (pthread_mutex_init(info->philo_tab[i].r_fork.mutex, NULL) == -1)
		{
			info->philo_tab[i].r_fork.init = 0;
			return (ft_error(5, info));
		}
		else
			info->philo_tab[i].r_fork.init = 1;
	}
	return (ft_give_forks(info));
}

int	ft_init_2(t_info *info)
{
	info->printf.mutex = malloc(sizeof(pthread_mutex_t));
	if (!info->printf.mutex)
		return (ft_error(3, info));
	if (pthread_mutex_init(info->printf.mutex, NULL) == -1)
	{
		info->printf.init = 0;
		return (ft_error(5, info));
	}
	return (ft_init_forks(info));
}

int	ft_init(t_info *info)
{
	int	i;

	i = -1;
	info->is_dead.mutex = malloc(sizeof(pthread_mutex_t));
	if (!info->is_dead.mutex)
		return (ft_error(3, info));
	if (pthread_mutex_init(info->is_dead.mutex, NULL) == -1)
	{
		info->is_dead.init = 0;
		return (ft_error(5, info));
	}
	else
	{
		info->is_dead.init = 1;
		info->is_dead.value = -1;
	}
	while (++i < info->philo_num)
	{
		info->philo_tab[i].index = i;
		info->philo_tab[i].meal_num = 0;
		info->philo_tab[i].last_meal = ft_convert(info->start);
		info->philo_tab[i].info = info;
	}
	return (ft_init_2(info));
}
