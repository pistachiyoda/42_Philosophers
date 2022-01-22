/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:27:37 by fmai              #+#    #+#             */
/*   Updated: 2022/01/22 14:13:38 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	check_input1(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][0] == '-' || argv[i][0] == '+')
			j ++;
		while (argv[i][j])
		{
			if (!is_digit(argv[i][j]))
				return (1);
			j ++;
		}
		i ++;
	}
	return (0);
}

int	check_input2(t_input_args args)
{
	if (args.number_of_philosophers < 1)
		return (1);
	if (args.time_to_die < 1)
		return (1);
	if (args.time_to_eat < 1)
		return (1);
	if (args.time_to_sleep < 1)
		return (1);
	if (args.is_must_eat == true
		&& args.number_of_times_each_philosopher_must_eat < 1)
		return (1);
	return (0);
}

int	parse_args(int argc, char **argv, t_info *info)
{
	if (argc < 5 || 6 < argc)
		return (1);
	if (check_input1(argc, argv))
		return (1);
	info->args.number_of_philosophers = atoi(argv[1]);
	info->args.time_to_die = atoi(argv[2]);
	info->args.time_to_eat = atoi(argv[3]);
	info->args.time_to_sleep = atoi(argv[4]);
	if (argc == 5)
	{
		info->args.is_must_eat = false;
		info->args.number_of_times_each_philosopher_must_eat = -1;
	}
	else
	{
		info->args.is_must_eat = true;
		info->args.number_of_times_each_philosopher_must_eat = atoi(argv[5]);
	}
	return (check_input2(info->args));
}
