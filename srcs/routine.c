/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:19:35 by nate              #+#    #+#             */
/*   Updated: 2024/08/07 07:43:01 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(int timer)
{
	timer *= 2;
	while (timer--)
		usleep(500);
}

void	lock_forks(t_philo *philo)
{
	if (philo->index % 2)
	{
		pthread_mutex_lock(philo->r_fork.mutex);
		pthread_mutex_lock(philo->info->printf.mutex);
		print_log(philo, 4);
		pthread_mutex_unlock(philo->info->printf.mutex);
		pthread_mutex_lock(philo->l_fork.mutex);
		pthread_mutex_lock(philo->info->printf.mutex);
		print_log(philo, 5);
		pthread_mutex_unlock(philo->info->printf.mutex);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork.mutex);	
		pthread_mutex_lock(philo->info->printf.mutex);
		print_log(philo, 5);
		pthread_mutex_unlock(philo->info->printf.mutex);
		pthread_mutex_lock(philo->r_fork.mutex);
		pthread_mutex_lock(philo->info->printf.mutex);
		print_log(philo, 4);
		pthread_mutex_unlock(philo->info->printf.mutex);
	}
}

void	unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(philo->r_fork.mutex);
	pthread_mutex_unlock(philo->l_fork.mutex);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->info->simu_start.mutex);
	pthread_mutex_unlock(philo->info->simu_start.mutex);
	if (philo->index % 2)
		usleep(1);
	while (1)
	{
		lock_forks(philo);
		pthread_mutex_lock(philo->info->printf.mutex);
		print_log(philo, 1);
		pthread_mutex_unlock(philo->info->printf.mutex);
		ft_sleep(philo->info->t_eat);
		unlock_forks(philo);
		pthread_mutex_lock(philo->info->printf.mutex);
		print_log(philo, 2);
		pthread_mutex_unlock(philo->info->printf.mutex);
		ft_sleep(philo->info->t_sleep);
		pthread_mutex_lock(philo->info->printf.mutex);
		print_log(philo, 3);
		pthread_mutex_unlock(philo->info->printf.mutex);
	}
}
