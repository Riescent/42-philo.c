/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:14:55 by vfries            #+#    #+#             */
/*   Updated: 2023/03/16 07:14:55 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

#include "this_is_not_my_libft.h"

#include "philosophers.h"
#include "philo_time.h"
#include "arguments.h"

static int	start_all_philosophers(t_philosopher *philosophers,
				pthread_mutex_t *execution_lock);
static void	failed_to_start_all_philosophers(t_philosopher *philosopher);

void	run_philosopher(t_philosopher *philosophers)
{
	int				size;
	pthread_mutex_t	execution_lock;

	if (pthread_mutex_init(&execution_lock, NULL) != 0)
	{
		printf("Failed to init execution_lock mutex\n");
		return ;
	}
	pthread_mutex_lock(&execution_lock);
	size = start_all_philosophers(philosophers, &execution_lock);
	pthread_mutex_unlock(&execution_lock);
	while (size--)
		pthread_join(philosophers[size].pthread, NULL);
	pthread_mutex_destroy(&execution_lock);
}

static int	start_all_philosophers(t_philosopher *philosophers,
				pthread_mutex_t *execution_lock)
{
	int	size;
	int	i;

	size = philosophers->args[NUMBER_OF_PHILOSOPHERS];
	if (size == 1)
	{
		pthread_mutex_lock(&philosophers->right_fork_mutex);
		philosophers->right_fork = true;
		pthread_mutex_unlock(&philosophers->right_fork_mutex);
	}
	i = -1;
	while (++i < size)
	{
		philosophers[i].execution_lock = execution_lock;
		if (pthread_create(&philosophers[i].pthread, NULL, &philosopher_routine,
				philosophers + i) != 0)
		{
			failed_to_start_all_philosophers(philosophers);
			return (i);
		}
	}
	return (size);
}

static void	failed_to_start_all_philosophers(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->philosopher_died_mutex);
	*philosopher->philosopher_died = true;
	pthread_mutex_unlock(philosopher->philosopher_died_mutex);
	printf("Failed to start all threads\n");
}
