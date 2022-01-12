/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 22:13:25 by fmai              #+#    #+#             */
/*   Updated: 2022/01/12 23:00:05 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void *task(task_args_t *args)
{
	for (int i = 0; i < 10; i++)
	{
    	pthread_mutex_lock(&args->global_args->mutex);
		args->global_args->counter ++;	
    	printf("thread: %d, counter: %d\n", args->index, args->global_args->counter);
		pthread_mutex_unlock(&args->global_args->mutex);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_info			info;
	pthread_t *threads;
	task_args_t *task_args_list;

	if (parse_args(argc, argv, &info) == 1)
		return (error());
	if (init_philos(&info) == 1)
		return (error());

	global_args_t global_args = {
		PTHREAD_MUTEX_INITIALIZER,
		0,
	};
	int threads_count = 4;

	threads = malloc(sizeof(pthread_t) * threads_count);
	task_args_list = malloc(sizeof(task_args_t) * threads_count);

	for (int i = 0; i < threads_count; i++)
	{
		task_args_list[i].index = i;
		task_args_list[i].global_args = &global_args;
		// pthread_create(&threads[i], NULL, (void *)task, &task_args_list[i]);
	}
	
	for (int i = 0; i < threads_count; i ++)
	{
		// pthread_join(threads[i], NULL);
	}
	free(threads);
}
