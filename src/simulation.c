/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:57:25 by fmai              #+#    #+#             */
/*   Updated: 2022/01/16 20:02:02 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	is_dead(t_philo_args *args)
{
	if (args->info->monitor.is_a_philosopher_dead)
		pthread_mutex_unlock(&args->info->monitor.dead);
	return (args->info->monitor.is_a_philosopher_dead);
}

int	take_fork_odd(t_philosopher *philo, t_philo_args *args)
{
	long long timestamp;

	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&args->info->monitor.dead);
	if (is_dead(args))
	{
		pthread_mutex_unlock(philo->right_fork);
		return (1);
	}
	printf(
		"%lld %d has taken right a fork\n",
		get_time(), args->index);
	pthread_mutex_unlock(&args->info->monitor.dead);

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&args->info->monitor.dead);
	if (is_dead(args))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	timestamp = get_time();
	printf(
		"%lld %d has taken left a fork\n%lld %d is eating\n",
		timestamp, args->index, timestamp, args->index);
	pthread_mutex_unlock(&args->info->monitor.dead);
	philo->lasttime_eat = timestamp;
	return (0);
}

int	take_fork_even(t_philosopher *philo, t_philo_args *args)
{
	long long timestamp;

	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&args->info->monitor.dead);
	if (is_dead(args))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	printf(
		"%lld %d has taken a left fork\n",
		get_time(), args->index);
	pthread_mutex_unlock(&args->info->monitor.dead);

	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&args->info->monitor.dead);
	if (is_dead(args))
	{
		pthread_mutex_unlock(philo->left_fork);
		return (1);
	}
	// timestamp = 0;
	timestamp = get_time();
	printf(
		"%lld %d has taken a right fork\n%lld %d is eating\n",
		timestamp, args->index, timestamp, args->index);
	pthread_mutex_unlock(&args->info->monitor.dead);
	philo->lasttime_eat = timestamp;
	return (0);
}

int	take_forks(t_philosopher *philo, bool *is_odd, t_philo_args *args)
{
	int	result;
	if (*is_odd)
		result = take_fork_odd(philo, args);
	else
		result = take_fork_even(philo, args);
	return (result);
}

int	put_fork_odd(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

int	put_fork_even(t_philosopher *philo)
{
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
	return (0);
}

int	put_fork(t_philosopher *philo, bool *is_odd)
{
	int	result;

	if (*is_odd)
		result = put_fork_odd(philo);
	else
		result = put_fork_even(philo);
	return (result);
}

void	philo_wait(long long prev_timestamp, int wait_msec)
{
	long long	timestamp;
	long long	target;

	target = prev_timestamp + (long long)wait_msec;
	// printf("index : %d / target : %lld\n", index, target);
	while (1)
	{
		timestamp = get_time();
		if (timestamp >= target)
			return;
		usleep(50);
	}
}

bool	eat(t_philo_args *args)
{
	t_philosopher	*me;
	bool			is_odd;
	long long		timestamp;
	
	me = &args->info->philosophers[args->index];
	is_odd = args->index % 2;
	while (1)
	{
		// take fork
		take_forks(me, &is_odd, args);
		// timestamp = get_time();
		pthread_mutex_lock(&args->info->monitor.dead);
		if (is_dead(args))
		{
			put_fork(me, &is_odd);
			return (false);
		}
		pthread_mutex_unlock(&args->info->monitor.dead);
		timestamp = args->info->philosophers[args->index].lasttime_eat; // 2本目のfolkが取れた時間
		philo_wait(timestamp, args->info->args.time_to_eat);
		// put fork
		put_fork(me, &is_odd);
		timestamp = get_time();	
		pthread_mutex_lock(&args->info->monitor.dead);
		if (is_dead(args))
			return (false);
		printf("%lld %d is sleeping\n", timestamp, args->index);
		pthread_mutex_unlock(&args->info->monitor.dead);
		philo_wait(timestamp, args->info->args.time_to_sleep);
		// timestamp = get_time();
		pthread_mutex_lock(&args->info->monitor.dead);
		if (is_dead(args))
			return (false);
		printf("%lld %d is thinking\n", get_time(), args->index);
		pthread_mutex_unlock(&args->info->monitor.dead);
	}
}

void	*simulation(void *_args)
{
	t_philo_args	*args;

	args = (t_philo_args *)_args;
	if (args->index % 2)
		usleep(200);
	eat(args);
	return (NULL);
}
