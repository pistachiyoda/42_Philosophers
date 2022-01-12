/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:13:25 by fmai              #+#    #+#             */
/*   Updated: 2022/01/12 11:29:12 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_philo_args *args;

	args = malloc(sizeof(t_philo_args) * 1);
	if (args == NULL)
		return(error());
	if (parse_args(argc, argv, args) == 1)
		return (error());
	
	printf("===check===\n");
	printf("args->number_of_philosophers:%d\n", args->number_of_philosophers);
	printf("args->time_to_die:%d\n", args->time_to_die);
	printf("args->time_to_eat:%d\n", args->time_to_eat);
	printf("args->time_to_sleep:%d\n", args->time_to_sleep);
	printf("args->number_of_times_each_philosopher_must_eat:%d\n", args->number_of_times_each_philosopher_must_eat);
}
