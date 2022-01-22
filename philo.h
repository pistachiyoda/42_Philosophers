/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:22:21 by fmai              #+#    #+#             */
/*   Updated: 2022/01/22 14:11:13 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

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

typedef struct s_monitor
{
	bool			is_a_philosopher_dead;
	pthread_mutex_t	dead;
}	t_monitor;
typedef struct s_philosopher
{
	int				number;
	long long		lasttime_eat;
	bool			is_must_eat;
	int				ate_cnt;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}	t_philosopher;

typedef struct s_info
{
	t_input_args		args;
	t_philosopher		*philosophers;
	t_monitor			monitor;
	pthread_mutex_t		*fork_mutexes;
}	t_info;

typedef struct s_philo_args {
	int		index;
	t_info	*info;
}	t_philo_args;

// src/atoi.c
int			atoi(const char *str);
int			is_digit(int c);

// src/parse_args.c
int			parse_args(int argc, char **argv, t_info *info);

// src/simulation.c
void		*simulation(void *args);

// src/error_handling.c
int			error(void);
int			all_free(t_info *info, t_philo_args *philo_args_list,
				pthread_t *philo_threads, pthread_t *monitor_threads);

// src/init_philos.c
int			init_philos(t_info *info);

// src/utils.c
long long	get_time(void);
int			is_dead(t_philo_args *args);
void		philo_wait(long long prev_timestamp, int wait_msec);

// src/monitor.c
void		*monitor(void *_args);

// src/handle_fork.c
int			handle_fork(t_philosopher *me, bool *is_odd, t_philo_args *args);

// src/handle_sleep.c
int			handle_sleep(t_philo_args *args);

// src/handle_think.c
int			handle_think(t_philo_args *args);
#endif
