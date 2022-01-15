/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 22:37:01 by fmai              #+#    #+#             */
/*   Updated: 2022/01/15 13:22:22 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	*monitor(void *_args)
{
	t_philo_args	*args;
	int				i;

	args = (t_philo_args *)_args;
	args->info->monitor.is_a_philosopher_dead = false;
	i = 0;
	while (!(args->info->monitor.is_a_philosopher_dead))
	{
		if (i == args->info->args.number_of_philosophers)
			i = 0;
		pthread_mutex_lock(&args->info->monitor.dead);
		if (args->info->philosophers[i].lasttime_eat + args->info->args.time_to_die
			< get_time())	
		{
			// printf("lasttime_eat : %lld\n", args->info->philosophers[i].lasttime_eat);
			// printf("time_to_die :       %d\n", args->info->args.time_to_die);
			// printf("sum :          %lld\n", args->info->philosophers[i].lasttime_eat + args->info->args.time_to_die);
			printf("%lld %d died\n", get_time(), i);
			args->info->monitor.is_a_philosopher_dead = true;
			pthread_mutex_unlock(&args->info->monitor.dead);
			return (NULL);
		}
		pthread_mutex_unlock(&args->info->monitor.dead);
		i++;
	}
	return (NULL);
}
