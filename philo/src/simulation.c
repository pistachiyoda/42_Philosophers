/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:57:25 by fmai              #+#    #+#             */
/*   Updated: 2022/01/19 15:27:50 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	eat(t_philo_args *args)
{
	t_philosopher	*me;
	bool			is_odd;

	me = &args->info->philosophers[args->index];
	is_odd = args->index % 2;
	while (1)
	{
		if (handle_fork(me, &is_odd, args) != 0)
			return ;
		if (handle_sleep(args) != 0)
			return ;
		if (handle_think(args) != 0)
			return ;
	}
}

void	*simulation(void *_args)
{
	t_philo_args	*args;

	args = (t_philo_args *)_args;
	if (args->index % 2)
		usleep(500);
	eat(args);
	return (NULL);
}
