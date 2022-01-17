/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_folk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 10:46:56 by fmai              #+#    #+#             */
/*   Updated: 2022/01/17 11:58:32 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	take_a_folk(t_philosopher *philo, t_philo_args *args,
	pthread_mutex_t *folk, bool goona_eat)
{
	if (pthread_mutex_lock(folk) != 0)
		return (1);
	if (pthread_mutex_lock(&args->info->monitor.dead) != 0)
		return (1);
	if (is_dead(args))
	{
		pthread_mutex_unlock(folk); //関数失敗時とis_deadがtrueの場合の処理の違いを調べる
		return (1);
	}
	if (goona_eat)
	{
		philo->lasttime_eat = get_time();
		printf(
			"%lld %d has taken a fork\n%lld %d is eating\n",
			philo->lasttime_eat, args->index, philo->lasttime_eat, args->index);
	}
	else
	{
		printf(
			"%lld %d has taken a fork\n",
			get_time(), args->index);
	}
	if (pthread_mutex_unlock(&args->info->monitor.dead) != 0)
		return (1);
	return (0);
}

int	take_forks(t_philosopher *philo, bool *is_odd, t_philo_args *args)
{
	if (*is_odd)
	{
		if (take_a_folk(philo, args, philo->right_fork, false) != 0)
			return (1);
		if (take_a_folk(philo, args, philo->left_fork, true) != 0)
			return (1);
	}
	else
	{
		if (take_a_folk(philo, args, philo->left_fork, false) != 0 )
			return (1);
		if (take_a_folk(philo, args, philo->right_fork, true) != 0)
			return (1);
	}
	return (0);
}

int	put_forks(t_philosopher *philo, bool *is_odd)
{
	if (*is_odd)
	{
		if (pthread_mutex_unlock(philo->left_fork) != 0)
			return (1);
		if (pthread_mutex_unlock(philo->right_fork) != 0)
			return (1);
	}
	else
	{
		if (pthread_mutex_unlock(philo->right_fork) != 0)
			return (1);
		if (pthread_mutex_unlock(philo->left_fork) != 0)
			return (1);
	}
	return (0);
}

// 0の時は正常系で哲学者が死んだ時、1の時は何かしらエラー、2の時は処理を続けたい時
int	handle_folk(t_philosopher *me, bool *is_odd, t_philo_args *args)
{
	if (take_forks(me, is_odd, args) != 0)
		return (1);
	if (pthread_mutex_lock(&args->info->monitor.dead) != 0)
		return (1);
	if (is_dead(args))	//todo: is_deadエラー時の処理
	{
		if (put_forks(me, is_odd) != 0)
			return (1);
		return (0);
	}
	if (pthread_mutex_unlock(&args->info->monitor.dead) != 0)
		return (1);
	philo_wait(args->info->philosophers[args->index].lasttime_eat,
		args->info->args.time_to_eat);
	if (put_forks(me, is_odd) != 0)
		return (1);
	return (2);
}
