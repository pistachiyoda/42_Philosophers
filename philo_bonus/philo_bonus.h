/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:22:21 by fmai              #+#    #+#             */
/*   Updated: 2022/01/24 14:46:43 by fmai             ###   ########.fr       */
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
# include	<fcntl.h>
# include	<sys/stat.h>
# include	<semaphore.h>
# include	<sys/types.h>
# include	<signal.h>


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

typedef struct s_philosopher
{
	int				number;
	long long		lasttime_eat;
	int				ate_cnt;
}	t_philosopher;

typedef struct s_info
{
	t_input_args		args;
	t_philosopher		philosopher;
	sem_t				*forks;
	sem_t				*waiter;
}	t_info;

// src/atoi.c
int			atoi(const char *str);
int			is_digit(int c);

// src/parse_args.c
int			parse_args(int argc, char **argv, t_info *info);

// src/utils.c
long long	get_time(void);
void		philo_wait(long long prev_timestamp, int wait_msec);

// src/proc_philo.c
void	proc_philo(t_info *info);
#endif
