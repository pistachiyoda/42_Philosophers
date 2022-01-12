/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:27:37 by fmai              #+#    #+#             */
/*   Updated: 2022/01/12 11:24:22 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_input(t_philo_args *args)
{
	if (args->number_of_philosophers < 1)
		return (1);
	if (args->time_to_die < 1)
		return (1);
	if (args->time_to_eat < 1)
		return (1);
	if (args->time_to_sleep < 1)
		return (1);
	if (args->is_must_eat == true
		&& args->number_of_times_each_philosopher_must_eat < 1)
		return (1);
	return (0);
}

int	parse_args(int argc, char **argv, t_philo_args *args)
{
	if (argc < 5 || 6 < argc)
		return(1);
	args->number_of_philosophers = atoi(argv[1]);
	args->time_to_die = atoi(argv[2]);
	args->time_to_eat = atoi(argv[3]);
	args->time_to_sleep = atoi(argv[4]);
	if (argc == 5)
	{
		args->is_must_eat = false;
		args->number_of_times_each_philosopher_must_eat = -1;
	}
	else
	{
		args->is_must_eat = true;
		args->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	}
	return (check_input(args));
}
