/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:30:33 by nate              #+#    #+#             */
/*   Updated: 2024/08/17 21:30:00 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_pars_next(t_info *info)
{
	if (info->philo_num < 1)
		return (ft_error(2, info));
	else if (info->t_die < 0)	
		return (ft_error(2, info));
	else if (info->t_eat < 0)	
		return (ft_error(2, info));
	else if (info->t_sleep < 0)	
		return (ft_error(2, info));
	else if (info->t_die > info->t_eat + info->t_die)
		return (ft_error(2, info));
	return (0);
}

int	ft_pars(char **av, t_info *info)
{
	info->philo_num = ft_atoi(av[1]);
	info->t_die = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	info->limit = -1;
	info->dead_philo = -1;
	if (av[5])
		info->limit = ft_atoi(av[5]);
	info->start = malloc(sizeof(struct timeval));
	if (!info->start)
		return (ft_error(3, info));
	if (gettimeofday(info->start, NULL) == -1)
		return (ft_error(4, info));
	info->printf.mutex = malloc(sizeof(pthread_mutex_t));
	if (!info->printf.mutex)
		return (ft_error(3, info));
	if (pthread_mutex_init(info->printf.mutex, NULL) == -1)
	{
		info->printf.init = 0;
		return (ft_error(5, info));
	}
	
	return (ft_pars_next(info));
}
