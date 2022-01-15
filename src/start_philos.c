/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 22:12:28 by fmai              #+#    #+#             */
/*   Updated: 2022/01/14 23:07:17 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	start_philos(t_info *info, t_philo_args *args, pthread_t *philo_threads, pthread_t *monitor_thread)
{
	int	i;

	pthread_mutex_init(&info->monitor.dead, NULL);

	i = 0;
	while (i < info->args.number_of_philosophers)
	{
		args[i].index = i;
		args[i].info = info;
		pthread_create(&philo_threads[i], NULL, simulation, &args[i]);
		i ++;
	}
	pthread_create(monitor_thread, NULL, monitor, &args);
	i = 0;
	while (i < info->args.number_of_philosophers)
	{
		pthread_join(philo_threads[i], NULL);
		i ++;
	}
	pthread_join(*monitor_thread, NULL);
	return (false);
}
