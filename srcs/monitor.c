/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:15:41 by nate              #+#    #+#             */
/*   Updated: 2024/08/10 08:28:40 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	Check if all the philosophers have eat all the meals (if there is a limit)
//		- Return 0 if they have not finished
//		- Reutnr 1 if they have finish
static int	check_meals(t_info *info)
{
	int	i;

	i = -1;
	pthread_mutex_lock(info->info.mutex);
	if (info->limit == -1)
	{
		pthread_mutex_unlock(info->info.mutex);
		return (0);
	}
	pthread_mutex_unlock(info->info.mutex);
	while (++i < info->nb_philo)
	{
		if (info->philo_tab[i].num_meal < info->limit)
		{
			pthread_mutex_unlock(info->info.mutex);
			return (0);
		}
	}
	info->all_eaten = 1;
	pthread_mutex_unlock(info->info.mutex);
	return (1);
}

// Check for all the philo if they have eat in the proper time
//		- Return 0 if there is no dead philospher
//		- Return 1 if there is a dead philosopher
static int	check_dead(t_info *info)
{
	int		i;
	long	actual_time;

	i = -1;
	pthread_mutex_lock(info->info.mutex);
	while (++i < info->nb_philo)
	{
		pthread_mutex_unlock(info->info.mutex);
		actual_time = ft_time(info);
		pthread_mutex_lock(info->info.mutex);
		if (actual_time > info->philo_tab[i].meal + info->t_die + 10)
		{
			info->isddead = i;
			pthread_mutex_unlock(info->info.mutex);
			return (1);
		}
		pthread_mutex_unlock(info->info.mutex);
		pthread_mutex_lock(info->info.mutex);
	}
	pthread_mutex_unlock(info->info.mutex);
	return (0);
}

// Just a loop that check every 200 usec if
//		- A philo is dead of starving
//		- All philo have eat
int	monitor(t_info *info)
{
	pthread_mutex_unlock(info->simu_start.mutex);
	while (1)
	{
		if (check_dead(info))
			return (ft_error(4, info));
		if (check_meals(info))
			return (ft_error(5, info));
		usleep(500);
	}
	return (0);
}
