/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:51:21 by nate              #+#    #+#             */
/*   Updated: 2024/09/16 17:36:45 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	destroy_threads(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
		pthread_join(info->philo_tab[i].thread, NULL);
}

//	Print the message associated to the error_code then return an int
int	ft_error(int code, t_info *info)
{
	pthread_mutex_lock(&info->is_dead.mutex);
	pthread_mutex_lock(&info->printf.mutex);
	if (code == 1)
		printf("Error\nArgs not valid\n");
	else if (code == 2)
		printf("Error\nError while GetTimeOfDay\n");
	else if (code == 3)
		printf("Error\nError creation mutex\n");
	else if (code == 4)
		printf("\n");
	else if (code == 5)
		print_log(5, &info->philo_tab[info->is_dead.value]);
	destroy_threads(info);
	if (code == 5)
		return (1);
	return (0);
}
