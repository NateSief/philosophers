/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 21:36:03 by nate              #+#    #+#             */
/*   Updated: 2024/08/07 07:39:44 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	init_forks(t_info *info)
{
	int	i;
	
	i = -1;
	while (++i < info->nb_philo)
	{
		info->philo_tab[i].r_fork.mutex = malloc(sizeof(pthread_mutex_t));
		if (!info->philo_tab[i].r_fork.mutex)
			ft_error(3, info);
		info->philo_tab[i].r_fork.init = 1;	
		pthread_mutex_init(info->philo_tab[i].r_fork.mutex, NULL);
	}
	i = -1;
	while (++i < info->nb_philo)
	{
		if (i == 0)
			info->philo_tab[i].l_fork = info->philo_tab[info->nb_philo - 1].r_fork;
		else
			info->philo_tab[i].l_fork = info->philo_tab[i - 1].r_fork;
	}
}

void	init_philo(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		info->philo_tab[i].index = i;
		info->philo_tab[i].info = info;
		info->philo_tab[i].meal = info->start;
		info->philo_tab[i].num_meal = 0;
	}
	init_forks(info);
}
