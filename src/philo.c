/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:57:25 by fmai              #+#    #+#             */
/*   Updated: 2022/01/07 21:55:01 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"
#include <stdio.h>

void	*philo(void *_args)
{
	t_philo_args	*args;

	args = (t_philo_args *)_args;
	printf("hoge: %d\n", args->time_to_eat);
	return (NULL);
}
