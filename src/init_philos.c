/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:34:13 by fmai              #+#    #+#             */
/*   Updated: 2022/01/12 22:59:42 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int set_forks(t_info *info)
{
	int				i;
	pthread_mutex_t	*fork_mutexes;

	fork_mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->args->number_of_philosophers);
	if (fork_mutexes == NULL)
		return (1);
	i = 0;
	while (i < info->args->number_of_philosophers)
	{
		if (i == 0)
			info->philosophers[i].left_fork = &fork_mutexes[info->args->number_of_philosophers];
		else
			info->philosophers[i].left_fork = &fork_mutexes[i - 1];
		info->philosophers[i].right_fork = &fork_mutexes[i];
		i++;
	}
	return (0);
}

int	init_philos(t_info *info)
{
	int i;

	info->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher) * info->args->number_of_philosophers);
	if (info->philosophers == NULL)
		return (1);
	i = 0;
	while (i < info->args->number_of_philosophers)
	{
		info->philosophers[i].number = i;
		info->philosophers[i].lefttime_to_die = info->args->time_to_die;
		info->philosophers[i].lefttime_to_eat = info->args->time_to_eat;
		info->philosophers[i].lefttime_to_sleep = info->args->time_to_sleep;
		info->philosophers[i].is_must_eat = info->args->is_must_eat;
		info->philosophers[i].must_eat_cnt = info->args->number_of_times_each_philosopher_must_eat;
		info->philosophers[i].ate_cnt = 0;
		i++;
	}
	return (set_forks(info));
}
