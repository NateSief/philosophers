/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:19:35 by nate              #+#    #+#             */
/*   Updated: 2024/08/08 13:43:53 by nate             ###   ########.fr       */
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
		print_log(philo, 4);
		pthread_mutex_lock(philo->l_fork.mutex);
		print_log(philo, 5);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork.mutex);	
		print_log(philo, 5);
		pthread_mutex_lock(philo->r_fork.mutex);
		print_log(philo, 4);
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
	if (philo->index % 2)
		usleep(1);
	while (1)
	{
		pthread_mutex_lock(philo->info->simu_start.mutex);
		pthread_mutex_unlock(philo->info->simu_start.mutex);
		lock_forks(philo);
		print_log(philo, 1);
		ft_sleep(philo->info->t_eat);
		philo->num_meal++;
		unlock_forks(philo);
		print_log(philo, 2);
		ft_sleep(philo->info->t_sleep);
		print_log(philo, 3);
	}
}
