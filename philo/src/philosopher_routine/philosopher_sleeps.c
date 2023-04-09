/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_sleeps.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:11 by vfries            #+#    #+#             */
/*   Updated: 2023/04/09 09:45:23 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_colors.h"

#include "philosophers.h"
#include "philo_time.h"
#include "arguments.h"

int	philosopher_sleeps(t_philosopher *philosopher)
{
	const struct timeval	current_time = get_current_time();
	struct timeval			time_to_sleep;

	if (print_state_change("%lli\t%i "BLACK_HIGH_INTENSITY"is sleeping\n"
			COLOR_RESET,
			philosopher) < 0)
		return (-1);
	time_to_sleep = current_time;
	timeval_add_ms(&time_to_sleep, philosopher->args[TIME_TO_SLEEP]);
	sleep_till(time_to_sleep, philosopher);
	return (0);
}
