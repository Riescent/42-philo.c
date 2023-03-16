/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:14:46 by vfries            #+#    #+#             */
/*   Updated: 2023/03/16 07:14:49 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

#include "philosophers.h"
#include "philo_time.h"

struct timeval	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (current_time.tv_usec >= NB_OF_USECONDS_IN_A_SECOND)
	{
		current_time.tv_sec += current_time.tv_usec
			/ NB_OF_USECONDS_IN_A_SECOND;
		current_time.tv_usec %= NB_OF_USECONDS_IN_A_SECOND;
	}
	return (current_time);
}

long long	get_timestamp(const t_philosopher *philosopher,
				const struct timeval current_time)
{
	return ((current_time.tv_sec - philosopher->start_time.tv_sec)
		* (long long)NB_OF_USECONDS_IN_A_MILLISECOND
		+ (current_time.tv_usec - philosopher->start_time.tv_usec)
		/ NB_OF_USECONDS_IN_A_MILLISECOND);
}

void	timeval_add_ms(struct timeval *tv, const int number_of_ms_to_add)
{
	tv->tv_usec += number_of_ms_to_add * NB_OF_USECONDS_IN_A_MILLISECOND;
	if (tv->tv_usec >= NB_OF_USECONDS_IN_A_SECOND)
	{
		tv->tv_sec += tv->tv_usec / NB_OF_USECONDS_IN_A_SECOND;
		tv->tv_usec %= NB_OF_USECONDS_IN_A_SECOND;
	}
}

int	timeval_compare(const struct timeval t1, const struct timeval t2)
{
	if (t1.tv_sec < t2.tv_sec)
		return (-1);
	if (t1.tv_sec > t2.tv_sec)
		return (1);
	if (t1.tv_usec < t2.tv_usec)
		return (-1);
	if (t1.tv_usec > t2.tv_usec)
		return (1);
	return (0);
}
