/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:13:25 by fmai              #+#    #+#             */
/*   Updated: 2022/01/19 10:27:21 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	handle_alone(t_info	*info)
{
	long long	timestamp;

	timestamp = get_time();
	printf("%lld %d has taken a fork\n", get_time(), 1);
	printf("%lld %d died\n", get_time() + info->args.time_to_die, 1);
	return (1);
}

int	start_philos(t_info *info, t_philo_args *args,
	pthread_t *philo_threads, pthread_t *monitor_threads)
{
	int	i;

	if (pthread_mutex_init(&info->monitor.dead, NULL) != 0)
		return (1);
	i = 0;
	while (i < info->args.number_of_philosophers)
	{
		args[i].index = i;
		args[i].info = info;
		pthread_create(&philo_threads[i], NULL, simulation, &args[i]);
		pthread_create(&monitor_threads[i], NULL, monitor, &args[i]);
		i ++;
	}
	return (0);
}

void	post_processing(t_info *info, pthread_t *philo_threads,
	pthread_t *monitor_threads, t_philo_args	*philo_args_list)
{
	int	i;

	i = 0;
	while (i < info->args.number_of_philosophers)
	{
		pthread_join(philo_threads[i], NULL);
		i ++;
	}
	pthread_join(*monitor_threads, NULL);
	pthread_mutex_destroy(&info->monitor.dead);
	while (i < info->args.number_of_philosophers)
	{
		pthread_mutex_destroy(info->philosophers[i].right_fork);
		free(info->philosophers[i].right_fork);
	}
	free(info->fork_mutexes);
	free(info->philosophers);
	free(philo_threads);
	free(monitor_threads);
	free(philo_args_list);
}

void	all_free(
	t_info *info,
	t_philo_args *philo_args_list, pthread_t *philo_threads, pthread_t *monitor_threads)
{
	free(info->philosophers);
	free(info->fork_mutexes);
	free(philo_args_list);
	free(philo_threads);
	free(monitor_threads);
}

int	main(int argc, char **argv)
{
	t_info			info;
	pthread_t		*philo_threads;
	pthread_t		*monitor_threads;
	t_philo_args	*philo_args_list;

	if (parse_args(argc, argv, &info) == 1)
		return (error());
	if (info.args.number_of_philosophers == 1)
		return (handle_alone(&info));
	if (init_philos(&info) == 1)
	{
		free(info.philosophers);
		free(info.fork_mutexes);
		return (error());
	}
	philo_args_list = malloc(sizeof(t_philo_args)
			* info.args.number_of_philosophers);
	philo_threads = malloc(sizeof(pthread_t)
			* info.args.number_of_philosophers);
	monitor_threads = malloc(sizeof(pthread_t)
			* info.args.number_of_philosophers);
	if (philo_args_list == NULL || philo_threads == NULL || monitor_threads == NULL)
	{
		all_free(&info, philo_args_list, philo_threads, monitor_threads);
		return (1);
	}
	if (start_philos(&info, philo_args_list, philo_threads, monitor_threads) != 0)
	{
		all_free(&info, philo_args_list, philo_threads, monitor_threads);
		return (1);
	}
	post_processing(&info, philo_threads, monitor_threads, philo_args_list);
}
