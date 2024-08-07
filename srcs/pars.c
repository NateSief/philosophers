/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:49:10 by nate              #+#    #+#             */
/*   Updated: 2024/08/07 07:50:12 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_pars(char **av, t_info *info)
{
	info->nb_philo = ft_atoi(av[1]);
	info->t_die = ft_atoi(av[2]);
	info->t_eat = ft_atoi(av[3]);
	info->t_sleep = ft_atoi(av[4]);
	info->limit = -1;
	if (av[5])
		info->limit = ft_atoi(av[5]);
	if (gettimeofday(&info->start, NULL) == -1)
		ft_error(2, info);
	info->simu_start.mutex = malloc(sizeof(pthread_mutex_t));
	if (!info->simu_start.mutex)
		ft_error(3, info);
	else
		info->simu_start.init = 1;
	info->printf.mutex = malloc(sizeof(pthread_mutex_t));
	if (!info->printf.mutex)
		ft_error(3, info);
	else
		info->printf.init = 1;
	pthread_mutex_init(info->simu_start.mutex, NULL);
	pthread_mutex_init(info->printf.mutex, NULL);
	
}
