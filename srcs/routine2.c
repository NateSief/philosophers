/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 14:59:45 by nate              #+#    #+#             */
/*   Updated: 2024/08/10 07:57:31 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_eat(t_philo *philo)
{
	lock_forks(philo);
	if (print_log(philo, 1))
	{
		unlock_forks(philo);
		return (1);			
	}
	philo->meal = ft_time(philo->info);
	pthread_mutex_lock(philo->info->info.mutex);
	if (ft_sleep(philo->info->t_eat, philo))
	{
		pthread_mutex_unlock(philo->info->info.mutex);
		unlock_forks(philo);
		return (1);
	}
	pthread_mutex_unlock(philo->info->info.mutex);
	unlock_forks(philo);
	return (0);
}

int	philo_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->info->info.mutex);
	if (print_log(philo, 2) || ft_sleep(philo->info->t_sleep, philo))
	{
		pthread_mutex_unlock(philo->info->info.mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->info->info.mutex);
	return (0);
}

int	philo_think(t_philo * philo)
{
	if (print_log(philo, 3))
		return (1);
	return (0);
}

int	routine_2(t_philo *philo)
{
	if (philo_eat(philo))
		return (1);
	philo->num_meal++;
	if (philo_sleep(philo))
		return (1);
	if (philo_think(philo))
		return (1);
	return (0);
}