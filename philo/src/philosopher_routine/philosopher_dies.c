/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_dies.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:18 by vfries            #+#    #+#             */
/*   Updated: 2023/04/10 18:40:04 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "tools.h"

#include "philosophers.h"
#include "philo_time.h"

bool	philosopher_dies(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->philosopher_died_mutex);
	if (*philosopher->philosopher_died == false)
		printf("%lli\t%i "RED"died\n"COLOR_RESET,
			get_timestamp(philosopher, get_current_time()), philosopher->id);
	*philosopher->philosopher_died = true;
	pthread_mutex_unlock(philosopher->philosopher_died_mutex);
	return (true);
}
