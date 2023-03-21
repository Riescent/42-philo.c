/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:26 by vfries            #+#    #+#             */
/*   Updated: 2023/03/16 07:15:26 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/semaphore.h>
#include <sys/fcntl.h>

#include "this_is_not_my_libft.h"

#include "philosophers.h"
#include "philosopher_semaphores.h"
#include "arguments.h"

static void	init_philosopher(t_philosopher	*philosopher, const int *args,
				const int id, sem_t *forks);

t_philosopher	*init_philosophers(const int *args)
{
	t_philosopher	*philosophers;
	int				i;
	sem_t			*forks;

	philosophers = malloc(sizeof(*philosophers) * args[NUMBER_OF_PHILOSOPHERS]);
	if (philosophers == NULL)
		return (NULL);
	forks = sem_open(FORKS_SEMAPHORE, O_CREAT, 0660, args[NUMBER_OF_PHILOSOPHERS]);
	if (forks == SEM_FAILED)
	{
		free(philosophers);
		return (NULL);
	}
	i = -1;
	while (++i < args[NUMBER_OF_PHILOSOPHERS])
		init_philosopher(philosophers + i, args, i + 1, forks);
	return (philosophers);
}

static void	init_philosopher(t_philosopher	*philosopher, const int *args,
				const int id, sem_t *forks)
{
	philosopher->id = id;
	philosopher->args = args;
	philosopher->forks = forks;
}
