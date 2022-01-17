/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sleep.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:21:56 by fmai              #+#    #+#             */
/*   Updated: 2022/01/17 22:05:40 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// 0の時は処理を続けたい時、1の時は正常系で哲学者が死んだ時、-1の時は何かしらエラー
int	handle_sleep(t_philo_args *args)
{
	long long timestamp;

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
