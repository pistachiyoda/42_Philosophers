/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_philos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 22:12:28 by fmai              #+#    #+#             */
/*   Updated: 2022/01/07 22:18:28 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	start_philos(t_philo_args base_args, t_philo_args *args, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < base_args.number_of_philosophers)
	{
		// @todo base_argsをargs[i]に詰め替える
		pthread_create(&threads[i], NULL, philo, &args[i]);
		i ++;
	}
	i = 0;
	while (i < base_args.number_of_philosophers)
	{
		pthread_join(threads[i], NULL);
		i ++;
	}
	return (false);
}
