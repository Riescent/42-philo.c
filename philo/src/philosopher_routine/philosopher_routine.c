/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:13 by vfries            #+#    #+#             */
/*   Updated: 2023/04/10 18:40:04 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "tools.h"

#include "philosophers.h"
#include "arguments.h"
#include "philo_time.h"

static void	init_philosopher_routine(t_philosopher *philosopher);

void	*philosopher_routine(void *philosopher)
{
	init_philosopher_routine(philosopher);
	while (true)
	{
		if (philosopher_eats(philosopher) < 0)
			return (NULL);
		if (philosopher_sleeps(philosopher) < 0)
			return (NULL);
		if (print_state_change("%lli\t%i "PURPLE"is thinking\n"COLOR_RESET,
				philosopher)
			< 0)
			return (NULL);
		usleep(100);
	}
}

static void	init_philosopher_routine(t_philosopher *philosopher)
{
	struct timeval	tmp;

	pthread_mutex_lock(philosopher->execution_lock);
	pthread_mutex_unlock(philosopher->execution_lock);
	philosopher->start_time = get_current_time();
	pthread_mutex_lock(&philosopher->time_to_die_mutex);
	philosopher->time_to_die = philosopher->start_time;
	timeval_add_ms(&philosopher->time_to_die, philosopher->args[TIME_TO_DIE]);
	pthread_mutex_unlock(&philosopher->time_to_die_mutex);
	if (philosopher->id % 2
		&& philosopher->args[TIME_TO_EAT] < philosopher->args[TIME_TO_DIE])
	{
		tmp = philosopher->start_time;
		timeval_add_ms(&tmp, philosopher->args[TIME_TO_EAT] * 9 / 10);
		sleep_till(tmp, philosopher);
	}
}
