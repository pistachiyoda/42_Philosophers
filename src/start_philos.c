/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 22:12:28 by fmai              #+#    #+#             */
/*   Updated: 2022/01/13 12:04:03 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	start_philos(t_info *info, t_philo_args *args, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < info->args.number_of_philosophers)
	{
		args[i].index = i;
		args[i].info = info;
		pthread_create(&threads[i], NULL, simulation, &args[i]);
		i ++;
	}
	i = 0;
	while (i < info->args.number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i ++;
	}
	return (false);
}
