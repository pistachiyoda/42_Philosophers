/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:13:25 by fmai              #+#    #+#             */
/*   Updated: 2022/01/24 13:24:28 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	handle_alone(t_input_args *args)
{
	long long	timestamp;

	timestamp = get_time();
	printf("%lld %d has taken a fork\n", get_time(), 1);
	printf("%lld %d died\n", get_time() + args->time_to_die, 1);
	return (1);
}

int	main(int argc, char **argv)
{
	t_input_args	args;

	if (parse_args(argc, argv, &args) == 1)
		return (1);
	if (args.number_of_philosophers == 1)
		return (handle_alone(&args));

	// TBD main
	printf("hoge\n");
}
