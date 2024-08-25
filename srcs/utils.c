/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 19:32:32 by nate              #+#    #+#             */
/*   Updated: 2024/08/22 15:43:37 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	Convert a struct timeval into a long value
long	ft_convert(struct timeval *to_convert)
{
	long	to_return;

	to_return = to_convert->tv_sec * 1000 + to_convert->tv_usec / 1000;
	return (to_return);
}

//	Get the actual time since the beggining of the simulation
long	ft_time(t_info *info)
{
	struct timeval	actual;
	long			to_return;

	if (gettimeofday(&actual, NULL) == -1)
		return (ft_error(3, info));
	to_return = ft_convert(&actual) - ft_convert(info->start);
	return (to_return);
}

//	Safe sleep function that check every 100 ms if the simulation is over or not
//		If not, redo it until all the timer value is over
int	ft_sleep(t_philo *philo, int value)
{
	int	loop;

	loop = value * 1000 / 500;
	while (loop--)
	{
		usleep(500);
		pthread_mutex_lock(philo->info->is_dead.mutex);
		if (philo->info->is_dead.value != -1)
		{
			pthread_mutex_unlock(philo->info->is_dead.mutex);
			return (1);
		}
		pthread_mutex_unlock(philo->info->is_dead.mutex);
	}
	return (0);
}

void	print_log(int state_value, t_philo *philo)
{
	if (state_value == 1)
		printf("%ld %d has taken a fork\n", ft_time(philo->info), philo->index);
	else if (state_value == 2)
		printf("%ld %d is eating %d \n", ft_time(philo->info), philo->index, philo->meal_num);
	else if (state_value == 3)
		printf("%ld %d is sleeping\n", ft_time(philo->info), philo->index);
	else if (state_value == 4)
		printf("%ld %d is thinking\n", ft_time(philo->info), philo->index);
	else if (state_value == 5)
		printf("%ld %d died\n", ft_time(philo->info), philo->index);
	else if (state_value == 5)
		printf("%ld %d all meals eat\n", ft_time(philo->info), philo->index);
	return ;
}

//	Just transform and char version of an int into the int value
int	ft_atoi(char *str)
{
	int	nb;
	int	sign;
	int	i;

	i = 0;
	nb = 0;
	sign = 0;
	if (str[0] == '-')
		sign = 1;
	else if (str[0] == '+')
		sign = 0;
	else
		i = -1;
	while (str[++i])
	{
		nb = nb * 10 + (str[i] - '0');
		if (nb >= 2147483647)
			return (-1);
	}
	if (sign == 1)
		return (-nb);
	return (nb);
}
