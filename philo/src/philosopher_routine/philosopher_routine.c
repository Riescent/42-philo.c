/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:13 by vfries            #+#    #+#             */
/*   Updated: 2023/04/03 04:25:58 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "ft_colors.h"

#include "philosophers.h"
#include "arguments.h"
#include "philo_time.h"

void	*philosopher_routine(void *philosopher_void)
{
	t_philosopher	*philosopher;

	philosopher = philosopher_void;
	pthread_mutex_lock(philosopher->execution_lock);
	pthread_mutex_unlock(philosopher->execution_lock);
	philosopher->start_time = get_current_time();
	pthread_mutex_lock(&philosopher->time_to_die_mutex);
	philosopher->time_to_die = philosopher->start_time;
	timeval_add_ms(&philosopher->time_to_die, philosopher->args[TIME_TO_DIE]);
	pthread_mutex_unlock(&philosopher->time_to_die_mutex);
//	if (philosopher->args[NUMBER_OF_PHILOSOPHERS] % 2 == 0
	if (philosopher->id % 2 == 0)
		usleep(2000);
	while (true)
	{
		if (philosopher_eats(philosopher) < 0)
			return (NULL);
		if (philosopher_sleeps(philosopher) < 0)
			return (NULL);
		if (print_state_change("%lli\t%i "PURPLE"is thinking\n"COLOR_RESET,
				get_timestamp(philosopher, get_current_time()), philosopher)
			< 0)
			return (NULL);
		usleep(300);
	}
}
