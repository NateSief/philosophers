/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:51:21 by nate              #+#    #+#             */
/*   Updated: 2024/09/25 17:25:58 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	destroy_threads(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo - 1)
	{
		pthread_join(info->philo_tab[i].thread, NULL);
		pthread_mutex_destroy(&info->forks[i].mutex);
		pthread_mutex_destroy(&info->meals[i].mutex);
		pthread_mutex_destroy(&info->timers[i].mutex);
	}
	pthread_mutex_destroy(&info->start.mutex);
	pthread_mutex_destroy(&info->info.mutex);
	pthread_mutex_destroy(&info->is_dead.mutex);
}

//	Print the message associated to the error_code then return an int
int	ft_error(int code, t_info *info)
{
	while (1)
	{
		pthread_mutex_lock(&info->info.mutex);
		if (info->info.value == 0)
		{
			pthread_mutex_unlock(&info->info.mutex);
			break ;
		}
		pthread_mutex_unlock(&info->info.mutex);
		usleep(100);
	}
	pthread_mutex_lock(&info->printf.mutex);
	if (code == 1)
		return (printf("Error\nArgs not valid\n"));
	else if (code == 2)
		printf("Error\nError while GetTimeOfDay\n");
	else if (code == 3)
		printf("Error\nError creation mutex\n");
	else if (code == 4)
		printf("All philosophers have eaten\n");
	else if (code == 5)
		print_log(5, &info->philo_tab[info->is_dead.value]);
	destroy_threads(info);
	return (0);
}
