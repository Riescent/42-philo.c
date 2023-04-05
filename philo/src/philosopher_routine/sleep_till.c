/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_till.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:05 by vfries            #+#    #+#             */
/*   Updated: 2023/03/16 07:15:06 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>

#include "philo_time.h"

long long	get_time_to_usleep(const struct timeval current_time,
								const struct timeval goal);

void	sleep_till(const struct timeval goal)
{
	struct timeval	current_time;
	long long		time_to_usleep;

	current_time = get_current_time();
	time_to_usleep = get_time_to_usleep(current_time, goal);
	usleep(time_to_usleep * (time_to_usleep > 0));
	while (timeval_compare(goal, current_time) > 0)  // TODO need to check if philosopher died
	{
		current_time = get_current_time();
	}
}

long long	get_time_to_usleep(const struct timeval current_time,
				const struct timeval goal)
{
	const long long	u_sec_to_usleep = goal.tv_usec - current_time.tv_usec;
	const long long sec_to_usleep = goal.tv_sec - current_time.tv_sec;

	return ((sec_to_usleep * NB_OF_USECONDS_IN_A_SECOND + u_sec_to_usleep)
		* 9 / 10);
}
