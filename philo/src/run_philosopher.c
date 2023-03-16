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

static void	set_philosopher_died_to_true_to_stop_all_thread(
				t_philosopher *philosopher);

void	run_philosopher(t_philosopher *philosophers, const int *args)
{
	int				size;
	int				i;
	pthread_mutex_t	execution_lock;

// TODO handle single philosopher
	if (pthread_mutex_init(&execution_lock, NULL) != 0)
	{
		printf("Failed to init execution_lock mutex\n");
		return ;
	}
	pthread_mutex_lock(&execution_lock);
	size = args[NUMBER_OF_PHILOSOPHERS];
	i = -1;
	while (++i < size)
	{
		philosophers[i].execution_lock = &execution_lock;
		if (pthread_create(&philosophers[i].pthread, NULL, &philosopher_routine,
				philosophers + i) != 0)
		{
			set_philosopher_died_to_true_to_stop_all_thread(philosophers);
			printf("Failed to start all threads\n");
			size = i;
			break ;
		}
	}
	pthread_mutex_unlock(&execution_lock);
	while (size--)
		pthread_join(philosophers[size].pthread, NULL);
	pthread_mutex_destroy(&execution_lock);
}

static void	set_philosopher_died_to_true_to_stop_all_thread(
				t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->philosopher_died_mutex);
	*philosopher->philosopher_died = true;
	pthread_mutex_unlock(philosopher->philosopher_died_mutex);
}
