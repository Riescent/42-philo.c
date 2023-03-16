/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_philosopher.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:28 by vfries            #+#    #+#             */
/*   Updated: 2023/03/16 07:15:29 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>

#include "philosophers.h"

void	destroy_philosophers(t_philosopher *philosophers, int size)
{
	while (size--)
		destroy_philosopher(philosophers + size);
	free(philosophers);
}

void	destroy_philosopher(t_philosopher *philosopher)
{
	pthread_mutex_destroy(&philosopher->right_fork_mutex);
}
