/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:19:35 by nate              #+#    #+#             */
/*   Updated: 2024/08/10 08:27:16 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_sleep(int timer, t_philo *philo)
{
	timer *= 2;
	while (timer-- && philo->info->isddead == -1 && !philo->info->all_eaten)
	{
		pthread_mutex_unlock(philo->info->info.mutex);
		usleep(500);
		pthread_mutex_lock(philo->info->info.mutex);
	}
	pthread_mutex_unlock(philo->info->info.mutex);
	pthread_mutex_lock(philo->info->info.mutex);
	if (philo->info->isddead != -1 || philo->info->all_eaten)
	{
		pthread_mutex_unlock(philo->info->info.mutex);
		return (1);
	}	
	pthread_mutex_unlock(philo->info->info.mutex);
	return (0);
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
	print_log(philo, 6);
	pthread_mutex_unlock(philo->l_fork.mutex);
	print_log(philo, 6);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		 i = 0;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->info->simu_start.mutex);
	pthread_mutex_unlock(philo->info->simu_start.mutex);
	if (philo->index % 2)
		usleep(1000);
	pthread_mutex_lock(philo->info->info.mutex);
	while (philo->info->isddead == -1)
	{
		pthread_mutex_unlock(philo->info->info.mutex);
		i++;
		if (routine_2(philo))
			break;
		pthread_mutex_lock(philo->info->info.mutex);
	}
	pthread_mutex_unlock(philo->info->info.mutex);
	return (NULL);
}
