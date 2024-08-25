/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:58:33 by nate              #+#    #+#             */
/*   Updated: 2024/08/25 08:29:20 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	Check if all the philosopher have eat
//		- Return 1 if they have all eat
//		- Return 0 if not
int	alleaten(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
	{
		if (info->philo_tab[i].meal_num < info->limit)
			return (0);
	}
	return (1);
}

// Check if a philosopher has died
//		If a philo have die, it return his id
//		Return -1 if not
int	isdead(t_info *info)
{
	int	i ;
	
	i = -1;
	while (++i < info->philo_num)
	{
		if (info->philo_tab[i].last_meal + info->t_die < ft_time(info))
		{
			pthread_mutex_lock(info->is_dead.mutex);
			info->is_dead.value = i;
			info->dead_philo = i;
			pthread_mutex_unlock(info->is_dead.mutex);
			return (i);
		}
	}
	return (-1);
}

//	Just a while loop that that check if a philo has died or if they have all
//		eat
int	monitor(t_info *info)
{
	while (1)
	{
		if (isdead(info) != -1)
			return (ft_error(6, info));
		else if (alleaten(info))
			return (ft_error(7, info));
		usleep(500);
	}
	return (1);
}
