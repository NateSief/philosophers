	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:22:54 by nate              #+#    #+#             */
/*   Updated: 2024/08/17 19:38:03 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	ft_clear_simu(t_info *info)
{
	int	i;
	
	i = -1;
	while (++i < info->philo_num)
	{
		if (info->philo_tab[i].r_fork.init)
		{
			pthread_mutex_destroy(info->philo_tab[i].r_fork.mutex);
			free(info->philo_tab[i].r_fork.mutex);
		}
		else
			break;
		pthread_join(info->philo_tab[i].thread, NULL);
	}
}

// int	ft_error_2(int error_code)
// {
	
// }

int	ft_who_died(t_info *info)
{
	int	to_return;
	
	pthread_mutex_lock(info->is_dead.mutex);
	to_return = info->dead_philo;
	pthread_mutex_unlock(info->is_dead.mutex);
	return (to_return);
	
}

int	ft_error(int error_code, t_info *info)
{
	ft_clear_simu(info);
	if (error_code == 1)
		return (printf("ERROR\nNot the good amount of arguments\n"));
	else if (error_code == 2)
		return (printf("ERROR\nThe args are not valid\n"));
	else if (error_code == 3)
		return (printf("Error\nBad malloc\n"));
	else if (error_code == 4)
		return (printf("Error\nGetTimeOfDay Bad allocation\n"));
	else if (error_code == 5)
		return (printf("Error\nPTHREAD_MUTEX INIT ERROR"));
	else if (error_code == 6)
		return (printf("%ld %d died\n", ft_time(info), ft_who_died(info)));
	else if (error_code == 7)
		return (printf("All philosopher have eat all their meals\n"));
	return (0);
}
