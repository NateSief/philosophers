/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:19:35 by nate              #+#    #+#             */
/*   Updated: 2024/08/09 14:06:36 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_sleep(int timer, t_philo *philo)
{
	timer *= 2;
	while (timer-- && philo->info->isddead == -1 && !philo->info->all_eaten)
		usleep(500);
	if (philo->info->isddead != -1 || philo->info->all_eaten)
		return (1);
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
	pthread_mutex_unlock(philo->l_fork.mutex);
}

int	routine_2(t_philo *philo)
{
	lock_forks(philo);
	if (print_log(philo, 1))
	{
		unlock_forks(philo);
		return (1);			
	}
	philo->meal = ft_time(philo->info);
	if (ft_sleep(philo->info->t_eat, philo))
	{
		unlock_forks(philo);
		return (1);
	}
	unlock_forks(philo);
	philo->num_meal++;
	if (print_log(philo, 2) || ft_sleep(philo->info->t_sleep, philo))
		return (1);
	if (print_log(philo, 3))
		return (1);
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	int		 i = 0;

	philo = (t_philo *)arg;
	if (philo->index % 2)
		usleep(1);
	pthread_mutex_lock(philo->info->simu_start.mutex);
	pthread_mutex_unlock(philo->info->simu_start.mutex);
	while (philo->info->isddead == -1)
	{
		i++;
		if (routine_2(philo))
			break;
	}
	return (NULL);
}
