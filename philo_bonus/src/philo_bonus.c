/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:13:25 by fmai              #+#    #+#             */
/*   Updated: 2022/01/24 15:31:01 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	handle_alone(t_info *info)
{
	long long	timestamp;

	timestamp = get_time();
	printf("%lld %d has taken a fork\n", get_time(), 1);
	printf("%lld %d died\n", get_time() + info->args.time_to_die, 1);
	return (1);
}

void	close_sems(t_info *info)
{
	sem_close(info->forks);
	sem_unlink("/forks");
	sem_close(info->waiter);
	sem_unlink("/waiter");
}

int	main(int argc, char **argv)
{
	t_info			info;
	int				pids[200];
	int				i;
	int				proc_status;

	if (parse_args(argc, argv, &info) == 1)
		return (1);
	if (info.args.number_of_philosophers == 1)
		return (handle_alone(&info));

	// init semaphore
	sem_unlink("/forks");
	sem_unlink("/waiter");
	info.forks = sem_open("/forks", O_CREAT, S_IRWXU, info.args.number_of_philosophers);
	if (info.forks == SEM_FAILED)
		return (1);
	info.waiter = sem_open("/waiter", O_CREAT, S_IRWXU, 1);
	if (info.waiter == SEM_FAILED)
	{
		sem_close(info.forks);
		sem_unlink("/forks");
		return (1);
	}
	// start philos
	i = 0;
	while (i < info.args.number_of_philosophers)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			kill(0, SIGINT);
			close_sems(&info);
			exit(1);
		}
		if (pids[i] == 0)
		{
			info.philosopher.number = i;
			info.philosopher.ate_cnt = 0;
			info.philosopher.lasttime_eat = get_time();
			proc_philo(&info);
		}
		i++;
	}
	// wait philos
	i = 0;
	while (i < info.args.number_of_philosophers)
	{
		waitpid(pids[i], &proc_status, WNOHANG);
		if (WIFEXITED(proc_status))
		{
			if (WEXITSTATUS(proc_status) == 1)
				printf("%lld %d died\n", get_time(), i + 1);
			close_sems(&info);
			kill(0, SIGINT);
			break;
		}
	}
	// close & unlink semaphore
	close_sems(&info);
}
