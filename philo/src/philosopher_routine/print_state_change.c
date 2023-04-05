/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state_change.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:08 by vfries            #+#    #+#             */
/*   Updated: 2023/04/05 19:38:05 by vfries           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "philosophers.h"

int	print_state_change(const char *format, const long long timestamp,
			t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->philosopher_died_mutex);
	if (*philosopher->philosopher_died)
	{
		pthread_mutex_unlock(philosopher->philosopher_died_mutex);
		return (-1);
	}
	printf(format, timestamp, philosopher->id); // TODO take timestamp here
	pthread_mutex_unlock(philosopher->philosopher_died_mutex);
	return (0);
}
