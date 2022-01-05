/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:27:37 by fmai              #+#    #+#             */
/*   Updated: 2022/01/05 22:46:27 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	parse_args(int argc, char **argv, t_philo_args *args)
{
	if (argc < 5 || argc > 6)
		return (false);
	args->number_of_philosophers = atoi(argv[1]);
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	if (argc == 5)
		args->number_of_times_each_philosopher_must_eat = -1;
	else
		args->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	return (true);
}
