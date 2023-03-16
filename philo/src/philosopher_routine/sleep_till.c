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

void	sleep_till(const struct timeval goal)
{
	const struct timeval	current_time = get_current_time();
	const long long			time_to_usleep
		= (goal.tv_sec - current_time.tv_sec)
		* (long long)NB_OF_USECONDS_IN_A_SECOND
		+ (goal.tv_usec - current_time.tv_usec);

	usleep(time_to_usleep * (time_to_usleep > 0));
}
