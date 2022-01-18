/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_think.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:34:07 by fmai              #+#    #+#             */
/*   Updated: 2022/01/18 12:00:30 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// 0:Continue processing, 1:Philo dead, -1:Error
int	handle_think(t_philo_args *args)
{
	if (pthread_mutex_lock(&args->info->monitor.dead) != 0)
		return (-1);
	if (is_dead(args) != 0)
		return (1);
	printf("%lld %d is thinking\n", get_time(), args->index + 1);
	if (pthread_mutex_unlock(&args->info->monitor.dead) != 0)
		return (-1);
	return (0);
}
