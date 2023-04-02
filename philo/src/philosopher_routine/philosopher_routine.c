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
	int				nb_of_times_to_eat;
	struct timeval	tmp;

	philosopher = philosopher_void;
	nb_of_times_to_eat = philosopher->args[NUMBER_OF_TIME_TO_EAT];
	pthread_mutex_lock(philosopher->execution_lock);
	pthread_mutex_unlock(philosopher->execution_lock);
	philosopher->start_time = get_current_time();
	philosopher->time_to_die = philosopher->start_time;
	timeval_add_ms(&philosopher->time_to_die, philosopher->args[TIME_TO_DIE]);
	if (philosopher->id % 2
		&& philosopher->args[TIME_TO_EAT] < philosopher->args[TIME_TO_DIE])
	{
		tmp = philosopher->start_time;
		timeval_add_ms(&tmp, philosopher->args[TIME_TO_EAT] / 2);
		sleep_till(tmp, philosopher);
	}
	while (no_philosophers_died(philosopher))
	{
		if (philosopher_eats(philosopher))
			return (NULL);
		if (nb_of_times_to_eat != -1)
			if (--nb_of_times_to_eat == 0)
				return (NULL);
		if (philosopher_sleeps(philosopher))
			return (NULL);
		print_state_change("%lli\t%i "PURPLE"is thinking\n"COLOR_RESET,
			get_timestamp(philosopher, get_current_time()), philosopher);
		usleep(300);
	}
	return (NULL);
}
