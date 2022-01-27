/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/27 12:18:50 by fmai              #+#    #+#             */
/*   Updated: 2022/01/27 15:09:04 by fmai             ###   ########.fr       */
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

void	kill_children(int count, int killed_pid, int *pids)
{
	int	i;

	i = 0;
	while (i < count)
	{
		if (pids[i] != killed_pid)
			kill(pids[i], SIGTERM);
		i++;
	}
}
