/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:45:21 by nate              #+#    #+#             */
/*   Updated: 2024/08/06 08:23:28 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	launch_philo(t_info *info)
{
	int	i;
	t_philo	*arg;

	i = -1;
	pthread_mutex_lock(info->simu_start.mutex);
	while (++i < info->nb_philo)
	{
		arg = &info->philo_tab[i];
		pthread_create(&info->philo_tab[i].thread, NULL, routine, (void *)arg);
	}
	monitor(info);
}

int	main(int ac, char **av)
{
	t_info	info;
	t_philo	philo[200];

	if (ac < 5 && ac > 6)
		ft_error(1, NULL);
	info.philo_tab = philo;
	ft_pars(av, &info);
	init_philo(&info);
	launch_philo(&info);
}
