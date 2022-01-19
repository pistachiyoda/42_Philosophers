/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 16:34:13 by fmai              #+#    #+#             */
/*   Updated: 2022/01/19 22:04:42 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	set_forks(t_info *info)
{
	int				i;
	pthread_mutex_t	*fork_mutexes;

	fork_mutexes = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* info->args.number_of_philosophers);
	if (fork_mutexes == NULL)
		return (1);
	info->fork_mutexes = fork_mutexes;
	i = 0;
	while (i < info->args.number_of_philosophers)
	{
		if (pthread_mutex_init(&fork_mutexes[i], NULL) != 0)
			return (1);
		if (i == 0)
			info->philosophers[i].left_fork
				= &fork_mutexes[info->args.number_of_philosophers - 1];
		else
			info->philosophers[i].left_fork = &fork_mutexes[i - 1];
		info->philosophers[i].right_fork = &fork_mutexes[i];
		i++;
	}
	return (0);
}

int	init_philos(t_info *info)
{
	int	i;
	info->philosophers = (t_philosopher *)malloc(sizeof(t_philosopher)
			* info->args.number_of_philosophers);
	if (info->philosophers == NULL)
		return (1);
	if (pthread_mutex_init(&info->monitor.dead, NULL) != 0)
		return (1);
	i = 0;
	while (i < info->args.number_of_philosophers)
	{
		info->philosophers[i].number = i;
		info->philosophers[i].lasttime_eat = get_time();
		info->philosophers[i].is_must_eat = info->args.is_must_eat;
		info->philosophers[i].ate_cnt = 0;
		i++;
	}
	return (set_forks(info));
}
