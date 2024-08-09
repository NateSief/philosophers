/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 13:15:41 by nate              #+#    #+#             */
/*   Updated: 2024/08/09 14:00:26 by nate             ###   ########.fr       */
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
	if (info->limit == -1)
		return (0);
	while (++i < info->nb_philo)
	{
		if (info->philo_tab[i].num_meal < info->limit)
			return (0);
	}
	info->all_eaten = 1;
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
	while (++i < info->nb_philo)
	{
		actual_time = ft_time(info);
		if (actual_time > info->philo_tab[i].meal + info->t_die)
		{
			info->isddead = i;
			printf("IS DEAD VALUE : %d \n", i );
			return (1);
		}
	}
	return (0);
}

void	monitor(t_info *info)
{
	pthread_mutex_unlock(info->simu_start.mutex);
	while (1)
	{
		if (check_dead(info))
		{
			ft_error(4, info);
			return ;
		}
		if (check_meals(info))
		{
			ft_error(5, info);
			return ;
		}
		usleep(100);
	}
}
