/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat_odd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:34:51 by nate              #+#    #+#             */
/*   Updated: 2024/09/25 17:26:41 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	Get the l_fork if the philo don't need to stop the simulation
static int	ft_rfork(t_philo *philo)
{
	if (ft_need_stop(philo))
		return (0);
	pthread_mutex_lock(&philo->r_fork->mutex);
	if (!ft_need_stop(philo))
	{
		pthread_mutex_lock(&philo->info->printf.mutex);
		print_log(1, philo);
		pthread_mutex_unlock(&philo->info->printf.mutex);
	}
	return (1);
}

//	Get the r_fork if the philo don't need to stop the simulation
static int	ft_lfork(t_philo *philo)
{
	if (ft_need_stop(philo))
		return (0);
	if (&philo->r_fork->mutex == &philo->l_fork->mutex)
		return (2);
	if (!ft_need_stop(philo))
	{
		pthread_mutex_lock(&philo->l_fork->mutex);
		if (ft_need_stop(philo))
		{
			pthread_mutex_unlock(&philo->l_fork->mutex);
			return (0);
		}
		pthread_mutex_lock(&philo->info->printf.mutex);
		print_log(1, philo);
		pthread_mutex_unlock(&philo->info->printf.mutex);
	}
	return (1);
}

//	Eat routine -> Try to get the two forks, and if the philo have the two forks
//		it eats then free the forks for the other philosophers to eat
int	ft_routine_eat_odd(t_philo *philo)
{
	if (ft_rfork(philo))
	{
		if (ft_lfork(philo) == 1)
		{
			pthread_mutex_lock(&philo->info->printf.mutex);
			print_log(2, philo);
			pthread_mutex_unlock(&philo->info->printf.mutex);
			pthread_mutex_lock(&philo->info->timers[philo->id].mutex);
			philo->info->timers[philo->id].value = ft_get_time(philo->info);
			pthread_mutex_unlock(&philo->info->timers[philo->id].mutex);
			usleep(philo->t_eat * 1000);
			pthread_mutex_lock(&philo->info->meals[philo->id].mutex);
			philo->info->meals[philo->id].value++;
			pthread_mutex_unlock(&philo->info->meals[philo->id].mutex);
			pthread_mutex_unlock(&philo->l_fork->mutex);
		}
		else if (ft_lfork(philo) == 2)
		{
			pthread_mutex_unlock(&philo->r_fork->mutex);
			return (usleep(philo->t_die * 1000), 1);
		}
		pthread_mutex_unlock(&philo->r_fork->mutex);
	}
	return (0);
}
