/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:13 by vfries            #+#    #+#             */
/*   Updated: 2023/03/16 07:15:14 by vfries           ###   ########lyon.fr   */
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
	while (true)
	{
		if (philosopher_eats(philosopher) < 0)
			return (NULL);
		pthread_mutex_lock(&philosopher->nb_of_times_to_eat_mutex);
		if (philosopher->nb_of_times_to_eat > 0)
			philosopher->nb_of_times_to_eat--;
		pthread_mutex_unlock(&philosopher->nb_of_times_to_eat_mutex);
		if (philosopher_sleeps(philosopher) < 0)
			return (NULL);
		if (print_state_change("%lli\t%i "PURPLE"is thinking\n"COLOR_RESET,
			get_timestamp(philosopher, get_current_time()), philosopher) < 0)
			return (NULL);
		usleep(300);
	}
}
