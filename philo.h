/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:22:21 by fmai              #+#    #+#             */
/*   Updated: 2022/01/12 11:13:39 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include	<stdbool.h>
# include	<pthread.h>
# include	<stdlib.h>
#include <stdio.h>

typedef struct s_philo_args
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	bool is_must_eat;
	int	number_of_times_each_philosopher_must_eat;
	int	index;
}	t_philo_args;

typedef struct {
	pthread_mutex_t mutex;
	int counter;
}	global_args_t;

typedef struct {
	int index;
	global_args_t *global_args;
}	task_args_t;

// src/atoi.c
int		atoi(const char *str);

// src/parse_args.c
int	parse_args(int argc, char **argv, t_philo_args *args);

// src/start_philos.c
bool	start_philos(t_philo_args base_args, t_philo_args *args, pthread_t *thread);

// src/philo.c
void	*philo(void *args);

// src/error_handling.c
int		error(void);

#endif
