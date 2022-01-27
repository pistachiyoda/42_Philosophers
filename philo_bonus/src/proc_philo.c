/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proc_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:02:51 by fmai              #+#    #+#             */
/*   Updated: 2022/01/27 23:38:46 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	take_fork(t_info *info, t_philosopher *philo)
{
	sem_wait(info->waiter);
	if (philo->lasttime_eat == -1)
	{
		sem_post(info->waiter);
		return (1);
	}
	sem_wait(info->forks);
	printf(
		"%lld %d has taken a fork\n", get_time(), philo->number + 1);
	sem_wait(info->forks);
	philo->lasttime_eat = get_time();
	printf(
		"%lld %d has taken a fork\n%lld %d is eating\n",
		philo->lasttime_eat, philo->number + 1,
		philo->lasttime_eat, philo->number + 1);
	sem_post(info->waiter);
	return (0);
}

void	put_fork(t_info *info, t_philosopher *philo)
{
	philo_wait(philo->lasttime_eat, info->args.time_to_eat);
	sem_post(info->forks);
	sem_post(info->forks);
	philo->ate_cnt ++;
	if (philo->ate_cnt
		== info->args.number_of_times_each_philosopher_must_eat)
		exit(0);
}

void	*thread_philo(void *_info)
{
	t_info			*info;
	t_philosopher	*philo;
	long long		timestamp;

	info = (t_info *)_info;
	philo = &info->philosopher;
	while (1)
	{
		if (take_fork(info, philo))
			break ;
		put_fork(info, philo);
		timestamp = get_time();
		printf("%lld %d is sleeping\n", timestamp, philo->number + 1);
		philo_wait(timestamp, info->args.time_to_sleep);
		printf("%lld %d is thinking\n", get_time(), philo->number + 1);
	}
	return (NULL);
}

void	*thread_monitor(void *_info)
{
	t_info	*info;

	info = (t_info *)_info;
	while (1)
	{
		sem_wait(info->waiter);
		if (info->philosopher.lasttime_eat
			+ info->args.time_to_die < get_time())
		{
			info->philosopher.lasttime_eat = -1;
			sem_post(info->waiter);
			return (NULL);
		}
		sem_post(info->waiter);
		usleep(500);
	}
	return (NULL);
}

void	proc_philo(t_info *info)
{
	pthread_t	monitor_thread;
	pthread_t	philo_thread;

	pthread_create(&monitor_thread, NULL, thread_monitor, info);
	pthread_create(&philo_thread, NULL, thread_philo, info);
	pthread_join(monitor_thread, NULL);
	pthread_join(philo_thread, NULL);
	exit(1);
}
