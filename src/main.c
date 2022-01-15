/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:13:25 by fmai              #+#    #+#             */
/*   Updated: 2022/01/15 15:36:25 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_info			info;
	pthread_t 		*philo_threads;
	pthread_t 		*monitor_threads;
	t_philo_args	*philo_args_list;

	if (parse_args(argc, argv, &info) == 1)
		return (error());
	if (init_philos(&info) == 1)
		return (error());
	philo_args_list = malloc(sizeof(t_philo_args) * info.args.number_of_philosophers);
	philo_threads = malloc(sizeof(pthread_t) * info.args.number_of_philosophers);
	monitor_threads = malloc(sizeof(pthread_t) * info.args.number_of_philosophers);
	start_philos(&info, philo_args_list, philo_threads, monitor_threads);
	free(philo_threads);
	free(philo_args_list);
}
