/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_eat.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:34:51 by nate              #+#    #+#             */
/*   Updated: 2024/09/19 13:34:36 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	Get the l_fork if the philo don't need to stop the simulation
static int	ft_lfork(t_philo *philo)
{
	if (ft_need_stop(philo))
		return(0);
	pthread_mutex_lock(&philo->l_fork->mutex);
	if (!ft_need_stop(philo))
	{
		pthread_mutex_lock(&philo->info->printf.mutex);
		print_log(1, philo);
		pthread_mutex_unlock(&philo->info->printf.mutex);
	}
	return (1);
}

//	Get the r_fork if the philo don't need to stop the simulation
static int	ft_rfork(t_philo *philo)
{
	if (ft_need_stop(philo))
		return(0);
	pthread_mutex_lock(&philo->r_fork->mutex);
	if (!ft_need_stop(philo))
	{
		pthread_mutex_lock(&philo->info->printf.mutex);
		print_log(1, philo);
		pthread_mutex_unlock(&philo->info->printf.mutex);
	}
	else
		return (0);
	return (1);
}

int	ft_routine_eat(t_philo *philo)
{
	if (ft_lfork(philo))
	{
		if (ft_rfork(philo))
		{
			pthread_mutex_lock(&philo->info->printf.mutex);
			print_log(2, philo);
			pthread_mutex_unlock(&philo->info->printf.mutex);
			philo->last_meal = ft_get_time(philo->info);
			if (ft_sleep(philo->t_sleep, philo))
			{
				philo->meal_num++;
				pthread_mutex_unlock(&philo->r_fork->mutex);
				pthread_mutex_unlock(&philo->l_fork->mutex);
				printf("%ld RENDU FOURCHETTES PAR %d\n",ft_get_time(philo->info), philo->id);
				return (1);
			}
			// usleep(philo->t_eat * 1000);
			pthread_mutex_lock(&philo->info->meals[philo->id].mutex);
			philo->info->meals[philo->id].value++;
			pthread_mutex_unlock(&philo->info->meals[philo->id].mutex);
			pthread_mutex_unlock(&philo->r_fork->mutex);
		}
		pthread_mutex_unlock(&philo->l_fork->mutex);
	}
	return (0);
}
