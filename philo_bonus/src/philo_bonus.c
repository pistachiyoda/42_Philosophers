/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:13:25 by fmai              #+#    #+#             */
/*   Updated: 2022/01/27 21:48:53 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo_bonus.h"

int	init_semaphore(t_info *info)
{
	sem_unlink("/forks");
	sem_unlink("/waiter");
	info->forks = sem_open(
			"/forks", O_CREAT, S_IRWXU, info->args.number_of_philosophers);
	if (info->forks == SEM_FAILED)
		return (1);
	info->waiter = sem_open("/waiter", O_CREAT, S_IRWXU, 1);
	if (info->waiter == SEM_FAILED)
	{
		sem_close(info->forks);
		sem_unlink("/forks");
		return (1);
	}
	return (0);
}

void	handle_fork_error(t_info *info, int *pids, int i)
{
	i --;
	while (i > -1)
	{
		kill(pids[i], SIGKILL);
		i --;
	}
	close_sems(info);
	exit(1);
}

void	start_philos(int *pids, t_info *info)
{
	int				i;

	i = 0;
	while (i < info->args.number_of_philosophers)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			handle_fork_error(info, pids, i);
		if (pids[i] == 0)
		{
			info->philosopher.number = i;
			info->philosopher.ate_cnt = 0;
			info->philosopher.lasttime_eat = get_time();
			proc_philo(info);
		}
		i++;
	}
}

void	wait_philos(int *pids, t_info *info)
{
	int	i;
	int	proc_status;
	int	finished_pid;

	i = 0;
	while (i < info->args.number_of_philosophers)
	{
		finished_pid = waitpid(-1, &proc_status, 0);
		if (WEXITSTATUS(proc_status) == 1)
		{
			i = 0;
			while (i < info->args.number_of_philosophers)
			{
				if (pids[i] == finished_pid)
				{
					kill_children(
						info->args.number_of_philosophers, pids[i], pids);
					printf("%lld %d died\n", get_time(), i + 1);
					return ;
				}
				i++;
			}
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_info			info;
	int				pids[200];

	if (parse_args(argc, argv, &info) == 1)
		return (1);
	if (info.args.number_of_philosophers == 1)
		return (handle_alone(&info));
	if (init_semaphore(&info) == 1)
		return (1);
	start_philos(pids, &info);
	wait_philos(pids, &info);
	close_sems(&info);
}
