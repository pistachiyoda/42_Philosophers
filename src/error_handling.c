/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 10:20:00 by fmai              #+#    #+#             */
/*   Updated: 2022/01/19 13:49:47 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	error(void)
{
	printf("Error\n");
	return (1);
}

int	all_free(t_info *info, t_philo_args *philo_args_list,
	pthread_t *philo_threads, pthread_t *monitor_threads)
{
	free(info->philosophers);
	free(info->fork_mutexes);
	free(philo_args_list);
	free(philo_threads);
	free(monitor_threads);
	return (error());
}
