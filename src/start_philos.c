/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 22:12:28 by fmai              #+#    #+#             */
/*   Updated: 2022/01/17 23:11:42 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	start_philos(t_info *info, t_philo_args *args, pthread_t *philo_threads, pthread_t *monitor_threads)
{
	int	i;

	pthread_mutex_init(&info->monitor.dead, NULL);
	i = 0;
	while (i < info->args.number_of_philosophers)
	{
		args[i].index = i;
		args[i].info = info;
		pthread_create(&philo_threads[i], NULL, simulation, &args[i]);
		pthread_create(&monitor_threads[i], NULL, monitor, &args[i]);
		i ++;
	}
	i = 0;
	while (i < info->args.number_of_philosophers)
	{
		pthread_join(philo_threads[i], NULL);
		i ++;
	}
	pthread_join(*monitor_threads, NULL);
	pthread_mutex_destroy(&info->monitor.dead);
	while (i < info->args.number_of_philosophers)
	{
		pthread_mutex_destroy(info->philosophers[i].right_fork);
		free(info->philosophers[i].right_fork);
	}
	free(info->fork_mutexes);
	free(info->philosophers);
	return (false);
}
