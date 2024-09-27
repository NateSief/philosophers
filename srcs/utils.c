/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nate <nate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 15:45:06 by nate              #+#    #+#             */
/*   Updated: 2024/09/27 10:27:53 by nate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

//	Get the actual timestamp as a long value
size_t	timestamp(void)
{
	struct timeval	actual;

	gettimeofday(&actual, NULL);
	return (actual.tv_sec * 1000 + actual.tv_usec / 1000);
}

//	Custom Itoa that returns -1 if the number is negative or if the string 
//		contains non-digits characters
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

// Get the time since the start of the simulation
long	ft_get_time(t_info *info)
{
	long	ret;
	size_t	actual;

	actual = timestamp();
	pthread_mutex_lock(&info->start.mutex);
	ret = actual - info->start.value;
	pthread_mutex_unlock(&info->start.mutex);
	return (ret);
}

// Print the log with the timer, the state and the philosopher doing it
void	print_log(int state, t_philo *ph)
{
	if (state == 1)
		printf("%ld %d has taken a fork\n", ft_get_time(ph->info), ph->id);
	else if (state == 2)
		printf("%ld %d is eating\n", ft_get_time(ph->info), ph->id);
	else if (state == 3)
		printf("%ld %d is sleeping\n", ft_get_time(ph->info), ph->id);
	else if (state == 4)
		printf("%ld %d is thinking\n", ft_get_time(ph->info), ph->id);
	else if (state == 5)
		printf("%ld %d died\n", ft_get_time(ph->info), ph->id);
}

//	Custom usleep that divide a big usleep into a lot of little usleeps
//		and also checks if I have to stop to sleep because of the end of the
//		simulation
int	ft_sleep(t_philo *philo, int timer)
{
	long	actual;
	long	end;

	actual = ft_get_time(philo->info) * 1000;
	end = actual + timer * 1000;
	printf("%ld %d should sleep until %ld\n", actual/1000, philo->id, end/1000);
	while (actual <= end)
	{
		if (end - actual <= 1000)
		{
			usleep(end - actual);
			return (0);
		}
		usleep(1000);
		pthread_mutex_lock(&philo->info->is_dead.mutex);
		if ((int)philo->info->is_dead.value >= 0 || \
			(int)philo->info->is_dead.value == -3)
		{
			pthread_mutex_unlock(&philo->info->is_dead.mutex);
			return (1);
		}
		pthread_mutex_unlock(&philo->info->is_dead.mutex);
		actual = ft_get_time(philo->info) * 1000;
	}
	return (0);
}
