/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:49:40 by nate              #+#    #+#             */
/*   Updated: 2024/08/07 07:45:09 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	Print the state of the philo
void	print_log(t_philo *philo, int state)
{
	if (state == 1)
	{
		printf("%ld %d is eating\n", ft_time(philo->info), philo->index);
		philo->num_meal++;
	}
	else if (state == 2)
		printf("%ld %d is sleeping\n", ft_time(philo->info), philo->index);
	else if (state == 3)
		printf("%ld %d is thinking\n", ft_time(philo->info), philo->index);
	else if (state == 4)
		printf("%ld %d has taken the right fork\n", \
			ft_time(philo->info), philo->index);
	else if (state == 5)
		printf("%ld %d has taken the left fork\n", \
			ft_time(philo->info), philo->index);
}

long	convert_time(struct timeval *timestamp)
{
	return (timestamp->tv_sec * 1000 + timestamp->tv_usec / 1000);
}

int	whosdead(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
	{
		if (info->philo_tab[i].isddead)
			return (i);
	}
	return (-1);
}

//	Return the actual timestamp since the beggining of the simulation
long	ft_time(t_info *info)
{
	struct timeval	actual;
	long			return_val;

	if (gettimeofday(&actual, NULL) == -1)
		ft_error(2, info);
	return_val = actual.tv_sec * 1000 + actual.tv_usec / 1000;
	return_val -= info->start.tv_sec * 1000 + info->start.tv_usec / 1000;
	return (return_val);
}

//	Simplified version of Atoi :
//		- IF the number overfloat 	-> return -1
//		- IF the number is negative	-> return -1
int	ft_atoi(char *str)
{
	long	num;
	int	i;

	i = -1;
	num = 0;
	if (str[0] == '-')
		return (-1);
	while (str[++i])
	{
		num = num * 10 + str[i] - '0';
		if (num > 2147483647 || num < 0)
			return (-1);
	}
	return ((int)num);
}
