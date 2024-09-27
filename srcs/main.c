/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:22:00 by nate              #+#    #+#             */
/*   Updated: 2024/09/26 15:47:04 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	Launch the threads on the routine then start the monitor
static int	launch_routine(t_info *info)
{
	int	i;

	pthread_mutex_lock(&info->start.mutex);
	info->start.value = timestamp();
	pthread_mutex_unlock(&info->start.mutex);
	i = -1;
	while (++i < info->nb_philo)
	{
		pthread_create(&info->philo_tab[i].thread, NULL, (void *)routine, \
			(void *)(&info->philo_tab[i]));
		info->info.value++;
		i++;
	}
	i = 0;
	while (++i < info->nb_philo)
	{
		pthread_create(&info->philo_tab[i].thread, NULL, (void *)routine, \
			(void *)(&info->philo_tab[i]));
		info->info.value++;
		i++;
	}
	return (monitor(info));
}

// Get if there is all the informations in the args, then launche the simulation
int	main(int ac, char **av, char **envp)
{
	t_info			info;
	t_philo			philo[PHILO_MAX];
	t_mutex			forks[PHILO_MAX];
	char			ret;

	if (!envp)
		return (printf("Need environment to run\n"));
	info.philo_tab = philo;
	info.forks = forks;
	if (ac != 6 && ac != 5)
		return (printf("Error\nNot the good amount of arguments !\n"));
	if (ft_init(&info, av) || ft_pars(&info))
		return (1);
	ret = launch_routine(&info);
	pthread_mutex_unlock(&info.printf.mutex);
	pthread_mutex_destroy(&info.printf.mutex);
	return (ret);
}
