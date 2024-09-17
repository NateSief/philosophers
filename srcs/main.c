/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:22:00 by nate              #+#    #+#             */
/*   Updated: 2024/09/17 14:07:36 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	launch_routine(t_info *info)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&info->info.mutex);
	info->start = timestamp();
	printf("T_die = %d, T_sleep = %d, T_eat = %d\n", info->t_die, info->t_sleep, info->t_eat);
	while (++i < info->nb_philo)
	{
		pthread_create(&info->philo_tab[i].thread, NULL, (void *)routine,\
			(void *)(&info->philo_tab[i]));
		info->active_threads++;
	}
	return (monitor(info));
}

// Get if there is all the informations in the args, then launche the simulation
int	main(int ac, char **av)
{
	t_info			info;
	t_philo			philo[PHILO_MAX];
	t_mutex			forks[PHILO_MAX];
	char			ret;

	info.philo_tab = philo;
	info.forks = forks;
	if (ac != 6 && ac != 5)
		return (printf("Error\nNot the good amount of arguments !\n"));
	if (ft_init(&info, av) || ft_pars(&info))
		return (1);
	ret = launch_routine(&info);
	pthread_mutex_unlock(&info.is_dead.mutex);
	pthread_mutex_unlock(&info.printf.mutex);
	return (ret);
}
