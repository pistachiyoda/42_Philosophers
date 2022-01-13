/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:57:25 by fmai              #+#    #+#             */
/*   Updated: 2022/01/13 13:59:21 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(t_philo_args *args)
{
	// t_philosopher	me;

	if (args->index % 2)
	{
		pthread_mutex_lock(args->info->philosophers[args->index].left_fork);
		pthread_mutex_lock(args->info->philosophers[args->index].right_fork);
		printf("%lld %d has taken a fork\n", get_time(), args->index);
		printf("%lld %d is eating\n", get_time(), args->index);
		usleep(args->info->args.time_to_eat);
		pthread_mutex_unlock(args->info->philosophers[args->index].left_fork);
		pthread_mutex_lock(args->info->philosophers[args->index].right_fork);
	}
	else
	{
		usleep(args->info->args.time_to_eat);
		pthread_mutex_lock(args->info->philosophers[args->index].left_fork);
		pthread_mutex_lock(args->info->philosophers[args->index].right_fork);
		printf("%lld %d has taken a fork\n", get_time(), args->index);
		printf("%lld %d is eating\n", get_time(), args->index);
		usleep(args->info->args.time_to_eat);
		pthread_mutex_unlock(args->info->philosophers[args->index].left_fork);
		pthread_mutex_lock(args->info->philosophers[args->index].right_fork);
	}
	printf("%lld %d is sleeping\n", get_time(), args->index);
	usleep(args->info->args.time_to_sleep);
}

void	*simulation(void *_args)
{
	t_philo_args	*args;

	args = (t_philo_args *)_args;
	while (1)
		eat(args);
	return (NULL);
}
