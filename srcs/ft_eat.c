/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:10:46 by nate              #+#    #+#             */
/*   Updated: 2024/08/25 08:30:42 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int    philo_l_fork(t_philo *philo)
{
    if (ft_need_stop(philo))
        return (0);
    pthread_mutex_lock(philo->l_fork->mutex);
    pthread_mutex_lock(philo->info->printf.mutex);
    if (!ft_need_stop(philo))
        print_log(1, philo);
    pthread_mutex_unlock(philo->info->printf.mutex);
    return (1);
}

int    philo_r_fork(t_philo *philo)
{
    if (ft_need_stop(philo))
    {
        pthread_mutex_unlock(philo->l_fork->mutex);
        return (0);
    }
    pthread_mutex_lock(philo->info->printf.mutex);
    if (!ft_need_stop(philo) && philo->meal_num < philo->info->limit)
    {
	    pthread_mutex_lock(philo->r_fork.mutex);
		print_log(1, philo);
		print_log(2, philo);
	}
	pthread_mutex_unlock(philo->info->printf.mutex);
    return (1);
}

//	Eat function that lock forks, sleep, unlock forks and increase the meal count
//		and the last meal timer
void	routine_eat(t_philo *philo)
{
	if (philo_l_fork(philo))
	{
		if (philo_r_fork(philo))
		{
			philo->last_meal = ft_time(philo->info);
			ft_sleep(philo, philo->t_eat);
			philo->meal_num++;
			pthread_mutex_unlock(philo->l_fork->mutex);
			pthread_mutex_unlock(philo->r_fork.mutex);
		}
		else
			pthread_mutex_unlock(philo->l_fork->mutex);
	}
}
