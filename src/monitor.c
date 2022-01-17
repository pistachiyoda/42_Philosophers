/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:37:01 by fmai              #+#    #+#             */
/*   Updated: 2022/01/17 22:23:05 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*monitor(void *_args)
{
	t_philo_args	*args;
	int				i;

	args = (t_philo_args *)_args;
	args->info->monitor.is_a_philosopher_dead = false;
	i = args->index;
	while (!(args->info->monitor.is_a_philosopher_dead))
	{
		if (args->info->philosophers[i].ate_cnt == args->info->args.number_of_times_each_philosopher_must_eat)
			return (NULL);
		pthread_mutex_lock(&args->info->monitor.dead);
		if (args->info->monitor.is_a_philosopher_dead)
		{
			pthread_mutex_unlock(&args->info->monitor.dead);
			return (NULL);
		}
		if (args->info->philosophers[i].lasttime_eat + args->info->args.time_to_die
			< get_time())	
		{
			printf("%lld %d died\n", get_time(), i + 1);
			args->info->monitor.is_a_philosopher_dead = true;
			pthread_mutex_unlock(&args->info->monitor.dead);
			return (NULL);
		}
		pthread_mutex_unlock(&args->info->monitor.dead);
		usleep(10);
	}
	return (NULL);
}
