/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:13:25 by fmai              #+#    #+#             */
/*   Updated: 2022/01/17 22:38:45 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

__attribute__((destructor))
static void destructor() {
    system("leaks philo");
}

int	handle_alone(t_info	*info)
{
	long long	timestamp;

	timestamp = get_time();
	printf("%lld %d has taken a fork\n", get_time(), 1);
	printf("%lld %d died\n", get_time() + info->args.time_to_die, 1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_info			info;
	pthread_t 		*philo_threads;
	pthread_t 		*monitor_threads;
	t_philo_args	*philo_args_list;

	if (parse_args(argc, argv, &info) == 1)
		return (error());
	if (info.args.number_of_philosophers == 1)
		return (handle_alone(&info));
	if (init_philos(&info) == 1)
		return (error());
	philo_args_list = malloc(sizeof(t_philo_args) * info.args.number_of_philosophers);
	philo_threads = malloc(sizeof(pthread_t) * info.args.number_of_philosophers);
	monitor_threads = malloc(sizeof(pthread_t) * info.args.number_of_philosophers);
	start_philos(&info, philo_args_list, philo_threads, monitor_threads);
	free(philo_threads);
	free(monitor_threads);
	free(philo_args_list);
}
