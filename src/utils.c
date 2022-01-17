/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 13:05:28 by fmai              #+#    #+#             */
/*   Updated: 2022/01/17 21:27:59 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long long	get_time(void)
{
	t_timeval time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	is_dead(t_philo_args *args)
{
	if (args->info->monitor.is_a_philosopher_dead)
	{
		if (pthread_mutex_unlock(&args->info->monitor.dead) != 0)
			return (-1);
	}
	return (args->info->monitor.is_a_philosopher_dead);
}

void	philo_wait(long long prev_timestamp, int wait_msec)
{
	long long	timestamp;
	long long	target;

	target = prev_timestamp + (long long)wait_msec;
	while (1)
	{
		timestamp = get_time();
		if (timestamp >= target)
			return;
		usleep(50);
	}
}
