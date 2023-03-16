/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_state_change.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:08 by vfries            #+#    #+#             */
/*   Updated: 2023/03/16 07:15:09 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "philosophers.h"

void	print_state_change(const char *format, const long long timestamp,
			t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->philosopher_died_mutex);
	if (*philosopher->philosopher_died)
	{
		pthread_mutex_unlock(philosopher->philosopher_died_mutex);
		return ;
	}
	pthread_mutex_unlock(philosopher->philosopher_died_mutex);
	printf(format, timestamp, philosopher->id);
}
