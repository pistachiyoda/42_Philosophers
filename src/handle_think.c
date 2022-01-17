/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_think.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 11:34:07 by fmai              #+#    #+#             */
/*   Updated: 2022/01/17 11:58:38 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

// 0の時は正常系で哲学者が死んだ時、1の時は何かしらエラー、2の時は処理を続けたい時
int	handle_think(t_philo_args *args)
{
	if (pthread_mutex_lock(&args->info->monitor.dead) != 0)
		return (1);
	if (is_dead(args)) //todo: is_deadエラー時の処理
		return (0);
	printf("%lld %d is thinking\n", get_time(), args->index);
	if (pthread_mutex_unlock(&args->info->monitor.dead) != 0)
		return (1);
	return (2);
}
		