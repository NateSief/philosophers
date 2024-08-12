/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:19:35 by nate              #+#    #+#             */
/*   Updated: 2024/08/12 13:35:02 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int	ft_sleep(int timer, t_philo *philo)
{
	timer *= 2;
	while (timer-- && philo->info->isddead == -1 && !philo->info->all_eaten)
		usleep(500);
	if (philo->info->isddead != -1 || philo->info->all_eaten)
	{
		pthread_mutex_unlock(philo->info->info.mutex);
		return (1);
	}	
	pthread_mutex_unlock(philo->info->info.mutex);
	return (0);
}

// Lock the forks for the philos, BUT:
//		- If there is only one philo in the simu, it has another behaviour
//			because it's an edge case and it manualy handle it
void	lock_forks(t_philo *philo)
{
	if (philo->info->nb_philo == 1)
	{
		pthread_mutex_lock(philo->r_fork.mutex);
		print_log(philo, 4);
		ft_sleep(philo->info->t_die, philo);
		pthread_mutex_unlock(philo->r_fork.mutex);
		return ;
	}
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
		usleep(1);
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
