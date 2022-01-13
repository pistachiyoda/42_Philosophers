/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:57:25 by fmai              #+#    #+#             */
/*   Updated: 2022/01/12 23:58:00 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

void	*philo(void *_args)
{
	t_philo_args	*args;
	t_philosopher	me;

	args = (t_philo_args *)_args;
	me = args->info->philosophers[args->index];
	printf("start philo: %d\n", me.number);
	return (NULL);
}
