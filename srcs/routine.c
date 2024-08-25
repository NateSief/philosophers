/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:56:01 by nate              #+#    #+#             */
/*   Updated: 2024/08/25 08:31:13 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	Tells if the philosopher has to stop or not
int		ft_need_stop(t_philo *philo)
{
	pthread_mutex_lock(philo->info->is_dead.mutex);
	if (philo->info->is_dead.value != -1)
	{
		pthread_mutex_unlock(philo->info->is_dead.mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->info->is_dead.mutex);
	pthread_mutex_lock(philo->r_fork.mutex);
	if (!philo->r_fork.init)
	{
		pthread_mutex_unlock(philo->r_fork.mutex);
		return (1);
	}
	pthread_mutex_unlock(philo->r_fork.mutex);
	return (0);

}

//	Sleep function that make the philosopher sleep
void	routine_sleep(t_philo *philo)
{
	pthread_mutex_lock(philo->info->printf.mutex);
	print_log(3, philo);
	pthread_mutex_unlock(philo->info->printf.mutex);
	ft_sleep(philo, philo->t_sleep);
}

//	Think function that make the philosopher think
void	routine_think(t_philo *philo)
{
	pthread_mutex_lock(philo->info->printf.mutex);
	print_log(3, philo);
	pthread_mutex_unlock(philo->info->printf.mutex);
}

//	Just a lopp where the philo eat, sleep and think and check beneath that if
//		the simulation should keep going
void	*routine(void *arg)
{
	t_philo *philo;
	int		i;

	i = 1;
	philo = (t_philo*) arg;
	usleep(philo->index % 2 * 500);
	while (i)
	{
		if (ft_need_stop(philo))
			break;
		routine_eat(philo);
		if (ft_need_stop(philo))
			break ;
		routine_sleep(philo);
		if (ft_need_stop(philo))
			break ;
		routine_think(philo);
		if (ft_need_stop(philo))
			break ;
	}
	// printf("LEAVE ROUTINE\n");
	return (NULL);
}
