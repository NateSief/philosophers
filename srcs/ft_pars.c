/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 10:23:13 by nate              #+#    #+#             */
/*   Updated: 2024/09/23 19:01:29 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_pars(t_info *info)
{
	if (info->t_die == -1)
		return (ft_error(1, info));
	if (info->t_eat == -1)
		return (ft_error(1, info));
	if (info->t_sleep == -1)
		return (ft_error(1, info));
	if (info->limit < -2 || info->limit == 0 || info->limit == -1)
		return (ft_error(1, info));
	if (info->nb_philo < 1 || info->nb_philo > PHILO_MAX)
		return (ft_error(1, info));
	return (0);
}
