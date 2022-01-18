/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:21:56 by fmai              #+#    #+#             */
/*   Updated: 2022/01/18 11:58:18 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// 0:Continue processing, 1:Philo dead, -1:Error
int	handle_sleep(t_philo_args *args)
{
	long long	timestamp;

	timestamp = get_time();
	if (pthread_mutex_lock(&args->info->monitor.dead) != 0)
		return (-1);
	if (is_dead(args) != 0)
		return (1);
	printf("%lld %d is sleeping\n", timestamp, args->index + 1);
	if (pthread_mutex_unlock(&args->info->monitor.dead) != 0)
		return (-1);
	philo_wait(timestamp, args->info->args.time_to_sleep);
	return (0);
}
