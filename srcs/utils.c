/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:45:06 by nate              #+#    #+#             */
/*   Updated: 2024/09/17 14:46:12 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	Custom Itoa that returns -1 if the number is negative or if the string contains
//		non-digits characters
int	ft_atoi(char *str)
{
	int	nb;
	int	i;

	i = -1;
	nb = 0;
	if (str[0] == '-')
		return (-1);
	while (str[++i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		nb = nb * 10 + (str[i] - '0');
	}
	return (nb);
}

// Custom sleep function -> Cut a big sleep into lot of 500 microseconds sleeps
//		and check in-between if it needs to stop
int	ft_sleep(int timer, t_philo *philo)
{
	int	loop;

	loop = timer * 1000 / 1000;
	while (loop--)
	{
		if (ft_need_stop(philo))
		{
			return (1);
		}
		usleep(1000);
	}
	return (0);
}

// Get the time since the start of the simulation
long	ft_get_time(t_info *info)
{
	long	ret;
	long	actual;

	actual = timestamp();
	ret = actual - info->start;
	return (ret);
}

// Print the log with the timer, the state and the philosopher doing it
void	print_log(int state, t_philo *philo)
{
	if (state == 1)
		printf("%ld %d has taken a fork\n", timestamp() - philo->info->start, philo->id);
	else if (state == 2)
		printf("%ld %d is eating\n", ft_get_time(philo->info), philo->id);
	else if (state == 3)
		printf("%ld %d is sleeping\n", ft_get_time(philo->info), philo->id);
	else if (state == 4)
		printf("%ld %d is thinking\n", ft_get_time(philo->info), philo->id);
	else if (state == 5)
		printf("%ld %d died\n", ft_get_time(philo->info), philo->id);
}
