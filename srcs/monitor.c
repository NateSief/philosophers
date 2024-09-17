/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:48:55 by nate              #+#    #+#             */
/*   Updated: 2024/09/17 14:11:08 by nate             ###   ########.fr       */
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
		if (info->philo_tab->meal_num < info->limit || info->limit <= 0)
			return (0);
	}
	return (1);
}

//	Simple loop that goes across all the philosophers to check if one of them
//		died because of starving
static int	ft_is_dead(t_info *info)
{
	pthread_mutex_lock(&info->is_dead.mutex);
	if (info->is_dead.value != -1)
	{
		pthread_mutex_unlock(&info->is_dead.mutex);
		return (1);
	}
	pthread_mutex_unlock(&info->is_dead.mutex);
	return (0);
}

//	While loop that check if I have a dead philo or if they have all ate there
//		meals
int	monitor(t_info *info)
{
	while (1)
	{
		// printf("LOOP MONITOR\n");
		if (ft_meals_check(info))
			return (ft_error(4, info));
		if (ft_is_dead(info))
			return (ft_error(5, info));
		usleep(500);
	}
}
