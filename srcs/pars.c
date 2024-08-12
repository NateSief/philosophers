/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:49:10 by nate              #+#    #+#             */
/*   Updated: 2024/08/09 14:52:51 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	check_values(t_info *info)
{
	if (info->nb_philo > 200 || info->nb_philo <= 0)
		return (ft_error(1, info));
	if (info->t_die == -1)
		return (ft_error(1, info));
	if (info->t_sleep == -1)
		return (ft_error(1, info));
	if (info->t_eat == -1)
		return (ft_error(1, info));
	if (info->limit == -1)
		return (ft_error(1, info));
	info->all_eaten = 0;
	info->isddead = -1;
	pthread_mutex_init(info->simu_start.mutex, NULL);
	pthread_mutex_init(info->printf.mutex, NULL);
	pthread_mutex_init(info->info.mutex, NULL);
	return (0);
}

int	ft_pars(char **av, t_info *info)
{
	info->nb_philo = ft_atoi(av[1]);
	info->t_die = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	if (av[5])
		info->limit = ft_atoi(av[5]);
	if (gettimeofday(&info->start, NULL) == -1)
		return (ft_error(2, info));
	info->simu_start.mutex = malloc(sizeof(pthread_mutex_t));
	if (!info->simu_start.mutex)
		return (ft_error(3, info));
	else
		info->simu_start.init = 1;
	info->printf.mutex = malloc(sizeof(pthread_mutex_t));
	if (!info->printf.mutex)
		return (ft_error(3, info));
	else
		info->printf.init = 1;
	info->info.mutex = malloc(sizeof(pthread_mutex_t));
	if (!info->info.mutex)
		return (ft_error(3, info));
	else
		info->info.init = 1;
	return (check_values(info));
}
