/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:48:55 by nate              #+#    #+#             */
/*   Updated: 2024/09/19 13:33:59 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	Simple loop that goes across all the philosopher to check if one of them
//		hasn't eat all his meal
static int	ft_meals_check(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		pthread_mutex_lock(&info->meals[i].mutex);
		if (info->meals[i].value < info->limit || info->limit <= 0)
		{
			pthread_mutex_unlock(&info->meals[i].mutex);
			return (0);
		}
		pthread_mutex_unlock(&info->meals[i].mutex);
	}
	return (1);
}

//	Simple loop that goes across all the philosophers to check if one of them
//		died because of starving
static int	ft_is_dead(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		if (info->philo_tab[i].last_meal + info->philo_tab[i].t_die <\
			timestamp() - info->start)
		{
			pthread_mutex_lock(&info->is_dead.mutex);
			info->is_dead.value = info->philo_tab[i].id;
			pthread_mutex_unlock(&info->is_dead.mutex);
			return (1);
		}		
	}
	return (0);
}

//	While loop that check if I have a dead philo or if they have all ate there
//		meals
int	monitor(t_info *info)
{
	pthread_mutex_unlock(&info->info.mutex);
	info->start = timestamp();
	while (1)
	{
		if (ft_meals_check(info))
		{
			pthread_mutex_lock(&info->is_dead.mutex);
			info->is_dead.value = -3;
			pthread_mutex_unlock(&info->is_dead.mutex);
			return (ft_error(4, info));
		}
		if (ft_is_dead(info))
			return (ft_error(5, info));
		usleep(500);
	}
}
