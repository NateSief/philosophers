/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:49:40 by nate              #+#    #+#             */
/*   Updated: 2024/08/10 08:16:04 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	Print the state of the philo
int	print_log(t_philo *philo, int state)
{
	if (philo->info->isddead != -1 || philo->info->all_eaten)
		return (1);
	pthread_mutex_lock(philo->info->printf.mutex);
	if (state == 1)
		printf("%ld %d is eating\n", ft_time(philo->info), philo->index);
	else if (state == 2)
		printf("%ld %d is sleeping\n", ft_time(philo->info), philo->index);
	else if (state == 3)
		printf("%ld %d is thinking\n", ft_time(philo->info), philo->index);
	else if (state == 4)
		printf("%ld %d has taken a fork\n", \
			ft_time(philo->info), philo->index);
	else if (state == 5)
		printf("%ld %d has taken a fork\n", \
			ft_time(philo->info), philo->index);
	else if (state == 6)
		printf("%ld %d has free a fork\n", \
			ft_time(philo->info), philo->index);
	pthread_mutex_unlock(philo->info->printf.mutex);
	return (0);
}

//	Convert struct timeval value into a long value
long	convert_time(struct timeval *timestamp)
{
	return (timestamp->tv_sec * 1000 + timestamp->tv_usec / 1000);
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
