/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:22:21 by fmai              #+#    #+#             */
/*   Updated: 2022/01/12 22:26:48 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include	<stdbool.h>
# include	<pthread.h>
# include	<stdlib.h>
# include	<stdio.h>

typedef struct s_philo_args
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	bool is_must_eat;
	int	number_of_times_each_philosopher_must_eat;
}	t_philo_args;

typedef struct s_philosopher
{
	int number;
	int lefttime_to_die;
	int	lefttime_to_eat;
	int	lefttime_to_sleep;
	bool is_must_eat;
	int	must_eat_cnt;
	int ate_cnt;
	pthread_mutex_t *right_fork;
	pthread_mutex_t *left_fork;
}	t_philosopher;

typedef struct s_info
{
	t_philo_args 	*args;
	t_philosopher 	*philosophers;
}	t_info;


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
int	parse_args(int argc, char **argv, t_info *info);

// src/start_philos.c
bool	start_philos(t_philo_args base_args, t_philo_args *args, pthread_t *thread);

// src/philo.c
void	*philo(void *args);

// src/error_handling.c
int		error(void);

// src/init_philos.c
int	init_philos(t_info *info);

#endif
