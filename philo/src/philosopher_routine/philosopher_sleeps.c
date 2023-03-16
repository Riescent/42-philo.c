/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_sleeps.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:11 by vfries            #+#    #+#             */
/*   Updated: 2023/03/16 07:15:11 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_colors.h"

#include "philosophers.h"
#include "philo_time.h"
#include "arguments.h"

bool	philosopher_sleeps(t_philosopher *philosopher)
{
	const struct timeval	current_time = get_current_time();
	struct timeval			time_to_sleep;

	print_state_change("%lli\t%i "BLACK_HIGH_INTENSITY"is sleeping\n"COLOR_RESET,
		get_timestamp(philosopher, current_time), philosopher);
	time_to_sleep = current_time;
	timeval_add_ms(&time_to_sleep, philosopher->args[TIME_TO_SLEEP]);
	if (timeval_compare(philosopher->time_to_die, time_to_sleep) <= 0)
	{
		sleep_till(philosopher->time_to_die);
		return (philosopher_dies(philosopher));
	}
	sleep_till(time_to_sleep);
	return (false);
}
