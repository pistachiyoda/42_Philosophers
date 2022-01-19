/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:21:56 by fmai              #+#    #+#             */
/*   Updated: 2022/01/19 17:18:21 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// 0:Continue processing, 1:Philo dead, -1:Error
int	handle_sleep(t_philo_args *args)
{
	long long	timestamp;

	timestamp = get_time();
	pthread_mutex_lock(&args->info->monitor.dead);
	if (is_dead(args) != 0)
		return (1);
	printf("%lld %d is sleeping\n", timestamp, args->index + 1);
	pthread_mutex_unlock(&args->info->monitor.dead);
	philo_wait(timestamp, args->info->args.time_to_sleep);
	return (0);
}
