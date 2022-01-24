/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:22:21 by fmai              #+#    #+#             */
/*   Updated: 2022/01/24 11:29:16 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include	<stdbool.h>
# include	<pthread.h>
# include	<stdlib.h>
# include	<stdio.h>
# include	<sys/time.h>
# include	<unistd.h>

typedef struct s_input_args
{
	int		number_of_philosophers;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	bool	is_must_eat;
	int		number_of_times_each_philosopher_must_eat;
}	t_input_args;

typedef struct timeval	t_timeval;

// src/atoi.c
int			atoi(const char *str);
int			is_digit(int c);

// src/parse_args.c
int			parse_args(int argc, char **argv, t_input_args *args);

// src/utils.c
long long	get_time(void);
#endif
