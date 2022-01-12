/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:27:37 by fmai              #+#    #+#             */
/*   Updated: 2022/01/12 16:31:21 by fmai             ###   ########.fr       */
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

int	parse_args(int argc, char **argv, t_info *info)
{
	if (argc < 5 || 6 < argc)
		return(1);
	info->args = malloc(sizeof(t_philo_args *) * 1);
	if (info->args == NULL)
		return (1);
	info->args->number_of_philosophers = atoi(argv[1]);
	info->args->time_to_die = atoi(argv[2]);
	info->args->time_to_eat = atoi(argv[3]);
	info->args->time_to_sleep = atoi(argv[4]);
	if (argc == 5)
	{
		info->args->is_must_eat = false;
		info->args->number_of_times_each_philosopher_must_eat = -1;
	}
	else
	{
		info->args->is_must_eat = true;
		info->args->number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	}
	return (check_input(info->args));
}
