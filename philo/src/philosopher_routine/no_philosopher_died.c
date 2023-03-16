/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_philosopher_died.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 14:18:53 by vfries            #+#    #+#             */
/*   Updated: 2023/03/16 14:18:54 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

bool	no_philosophers_died(const t_philosopher *philosopher)
{
	bool	return_value;

	pthread_mutex_lock(philosopher->philosopher_died_mutex);
	return_value = *philosopher->philosopher_died == false;
	pthread_mutex_unlock(philosopher->philosopher_died_mutex);
	return (return_value);
}
