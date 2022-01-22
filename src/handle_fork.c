/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fork.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 10:46:56 by fmai              #+#    #+#             */
/*   Updated: 2022/01/22 20:19:11 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	take_a_fork(t_philosopher *philo, t_philo_args *args,
	pthread_mutex_t *fork, bool goona_eat)
{
	pthread_mutex_lock(fork);
	pthread_mutex_lock(&args->info->monitor.dead);
	if (is_dead(args) != 0)
	{
		pthread_mutex_unlock(fork);
		return (-1);
	}
	if (goona_eat)
	{
		philo->lasttime_eat = get_time();
		printf(
			"%lld %d has taken a fork\n%lld %d is eating\n",
			philo->lasttime_eat, args->index + 1,
			philo->lasttime_eat, args->index + 1);
	}
	else
	{
		printf(
			"%lld %d has taken a fork\n", get_time(), args->index + 1);
	}
	pthread_mutex_unlock(&args->info->monitor.dead);
	return (0);
}

int	take_forks(t_philosopher *philo, bool *is_odd, t_philo_args *args)
{
	if (*is_odd)
	{
		if (take_a_fork(philo, args, philo->right_fork, false) != 0)
			return (-1);
		if (take_a_fork(philo, args, philo->left_fork, true) != 0)
		{
			pthread_mutex_unlock(philo->right_fork);
			return (-1);
		}
	}
	else
	{
		if (take_a_fork(philo, args, philo->left_fork, false) != 0 )
			return (-1);
		if (take_a_fork(philo, args, philo->right_fork, true) != 0)
		{
			pthread_mutex_unlock(philo->left_fork);
			return (-1);
		}
	}
	return (0);
}

void	put_forks(t_philosopher *philo, bool *is_odd)
{
	if (*is_odd)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
}

// 0:Continue processing, 1:Philo dead, -1:Error
int	handle_fork(t_philosopher *me, bool *is_odd, t_philo_args *args)
{
	if (take_forks(me, is_odd, args) != 0)
		return (-1);
	pthread_mutex_lock(&args->info->monitor.dead);
	if (is_dead(args) != 0)
	{
		put_forks(me, is_odd);
		return (1);
	}
	pthread_mutex_unlock(&args->info->monitor.dead);
	philo_wait(me->lasttime_eat,
		args->info->args.time_to_eat);
	put_forks(me, is_odd);
	me->ate_cnt ++;
	if (me->ate_cnt
		== args->info->args.number_of_times_each_philosopher_must_eat)
		return (1);
	return (0);
}
