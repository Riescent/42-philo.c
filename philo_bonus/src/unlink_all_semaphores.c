/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink_all_semaphores.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:25:24 by vfries            #+#    #+#             */
/*   Updated: 2023/03/22 15:25:25 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/semaphore.h>

#include "philosopher_semaphores.h"

void	unlink_all_semaphores(void)
{
	sem_unlink(EXECUTION_SEMAPHORE);
	sem_unlink(FORKS_SEMAPHORE);
	sem_unlink(PHILOSOPHER_DIED_SEMAPHORE);
	sem_unlink(TIME_TO_DIE_SEMAPHORE);
}
