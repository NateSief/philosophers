/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:35:11 by nate              #+#    #+#             */
/*   Updated: 2024/09/25 17:28:15 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Check if a philo died or if this philo died of starving
int	ft_need_stop(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->is_dead.mutex);
	if ((int)philo->info->is_dead.value != -2 \
		&& (int)philo->info->is_dead.value != -1)
	{
		pthread_mutex_unlock(&philo->info->is_dead.mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->info->is_dead.mutex);
	return (0);
}

//	Sleep routine function -> Make the philosopher sleep, and if there is an
//		error it will return 1, else 0;
static int	ft_routine_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->printf.mutex);
	print_log(3, philo);
	pthread_mutex_unlock(&philo->info->printf.mutex);
	usleep(philo->t_sleep * 1000);
	return (0);
}

//	Think routine function -> print the thinking message, and if there is an
//		error it will return 1, else 0;
static int	ft_routine_think(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->printf.mutex);
	print_log(4, philo);
	pthread_mutex_unlock(&philo->info->printf.mutex);
	return (0);
}

//	Routine for the philosophers to eat, sleep then think
void	*routine(void *arg)
{
	t_philo	philo;

	philo = *(t_philo *)arg;
	while (1)
	{
		if (philo.id % 2)
		{
			if (ft_need_stop(&philo) || ft_routine_eat(&philo))
				break ;
		}
		else
		{
			if (ft_need_stop(&philo) || ft_routine_eat_odd(&philo))
				break ;
		}
		if (ft_need_stop(&philo) || ft_routine_sleep(&philo))
			break ;
		if (ft_need_stop(&philo) || ft_routine_think(&philo))
			break ;
	}
	pthread_mutex_lock(&philo.info->info.mutex);
	philo.info->info.value--;
	pthread_mutex_unlock(&philo.info->info.mutex);
	return (NULL);
}
