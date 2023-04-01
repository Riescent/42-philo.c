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
	struct timeval	current_time;

	current_time = get_current_time();
	while (timeval_compare(goal, current_time) > 0)
	{
		usleep(100);
		current_time = get_current_time();
	}
}