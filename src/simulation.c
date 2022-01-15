/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:57:25 by fmai              #+#    #+#             */
/*   Updated: 2022/01/15 14:23:05 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	is_dead(t_philo_args *args)
{
	if (args->info->monitor.is_a_philosopher_dead)
		pthread_mutex_unlock(&args->info->monitor.dead);
	return (args->info->monitor.is_a_philosopher_dead);
}

int	take_fork_odd(t_philosopher philo)
{
	pthread_mutex_lock(philo.right_fork);
	pthread_mutex_lock(philo.left_fork);
	return (0);
}

int	take_fork_even(t_philosopher philo)
{
	usleep(200);
	pthread_mutex_lock(philo.left_fork);
	pthread_mutex_lock(philo.right_fork);
	return (0);
}

int	take_fork(t_philosopher philo, bool is_odd)
{
	int	result;
	if (is_odd)
		result = take_fork_odd(philo);
	else
		result = take_fork_even(philo);
	return (result);
}

int	put_fork_odd(t_philosopher philo)
{
	pthread_mutex_unlock(philo.left_fork);
	pthread_mutex_unlock(philo.right_fork);
	return (0);
}

int	put_fork_even(t_philosopher philo)
{
	pthread_mutex_unlock(philo.right_fork);
	pthread_mutex_unlock(philo.left_fork);
	return (0);
}

int	put_fork(t_philosopher philo, bool is_odd)
{
	int	result;

	if (is_odd)
		result = put_fork_odd(philo);
	else
		result = put_fork_even(philo);
	return (result);
}

bool	eat(t_philo_args *args)
{
	t_philosopher	me;
	bool			is_odd;
	
	me = args->info->philosophers[args->index];
	is_odd = args->index % 2;
	// take fork
	take_fork(me, is_odd);
	pthread_mutex_lock(&args->info->monitor.dead);
	if (is_dead(args))
	{
		put_fork(me, is_odd);
		return (false);
	}
	printf("%lld %d has taken a fork\n", get_time(), args->index);
	printf("%lld %d is eating\n", get_time(), args->index);
	pthread_mutex_unlock(&args->info->monitor.dead);
	args->info->philosophers[args->index].lasttime_eat = (long long)get_time();
	usleep(args->info->args.time_to_eat * 1000);	
	pthread_mutex_lock(&args->info->monitor.dead);
	// put fork
	put_fork(me, is_odd);
	if (is_dead(args))
		return (false);
	printf("%lld %d is sleeping\n", get_time(), args->index);
	pthread_mutex_unlock(&args->info->monitor.dead);
	usleep(args->info->args.time_to_sleep * 1000);
	pthread_mutex_lock(&args->info->monitor.dead);
	if (is_dead(args))
		return (false);
	printf("%lld %d is thinking\n", get_time(), args->index);
	pthread_mutex_unlock(&args->info->monitor.dead);
	return (true);
}

void	*simulation(void *_args)
{
	t_philo_args	*args;

	args = (t_philo_args *)_args;
	while (eat(args));
	return (NULL);
}
