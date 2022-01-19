/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_think.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:34:07 by fmai              #+#    #+#             */
/*   Updated: 2022/01/19 17:18:32 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// 0:Continue processing, 1:Philo dead, -1:Error
int	handle_think(t_philo_args *args)
{
	pthread_mutex_lock(&args->info->monitor.dead);
	if (is_dead(args) != 0)
		return (1);
	printf("%lld %d is thinking\n", get_time(), args->index + 1);
	pthread_mutex_unlock(&args->info->monitor.dead);
	return (0);
}
