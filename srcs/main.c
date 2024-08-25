/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 21:12:10 by nate              #+#    #+#             */
/*   Updated: 2024/08/25 07:38:22 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	launch_routine(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->philo_num)
		CREATE_THREAD;
	return (monitor(info));
}

int main(int ac, char **av)
{
	t_philo	philo[200];
	t_info	info;

	info.philo_tab = philo;
	if (ac != 5 && ac != 6)
		return (ft_error(1, &info));
	else if (ft_pars(av, &info) || ft_init(&info))
		return (ft_error(2, &info));
	else
		return (launch_routine(&info));
}
