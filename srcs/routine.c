/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:35:11 by nate              #+#    #+#             */
/*   Updated: 2024/09/17 14:05:44 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// Check if a philo died or if this philo died of starving
int	ft_need_stop(t_philo *philo)
{
	if (philo->last_meal + philo->t_die < timestamp() - philo->info->start)
	{
		printf("%ld PHILO %d DIED OF STARVING\n", ft_get_time(philo->info), philo->id);
		pthread_mutex_lock(&philo->info->is_dead.mutex);
		philo->info->is_dead.value = philo->id;
		pthread_mutex_unlock(&philo->info->is_dead.mutex);
		return (1);
	}
	pthread_mutex_lock(&philo->info->is_dead.mutex);
	if (philo->info->is_dead.value != -2 && philo->info->is_dead.value != -1)
	{
		printf("IS_DEAD VALUE ERROR\n");
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
	if (ft_sleep(philo->t_sleep, philo))
		return (1);
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
	usleep(philo.id % 2 * 2000);
	while (1)
	{
		if (ft_routine_eat(&philo) || ft_need_stop(&philo))
			break;
		if (ft_routine_sleep(&philo) || ft_need_stop(&philo))
			break;
		if (ft_routine_think(&philo) || ft_need_stop(&philo))
			break;
	}
	if (ft_need_stop(&philo))
		printf("SORTIE ROUTINE %d\n", philo.id);
	pthread_mutex_lock(&philo.info->info.mutex);
	philo.info->active_threads--;
	pthread_mutex_unlock(&philo.info->info.mutex);
	return (NULL);
}
