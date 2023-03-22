/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philosophers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:26 by vfries            #+#    #+#             */
/*   Updated: 2023/03/22 15:28:49 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/semaphore.h>
#include <sys/fcntl.h>

#include "this_is_not_my_libft.h"

#include "philosophers.h"
#include "philosopher_semaphores.h"
#include "arguments.h"

static int	init_philosopher(t_philosopher	*philosopher, const int *args,
				const int id, sem_t *forks);

t_philosopher	*init_philosophers(const int *args)
{
	t_philosopher	*philosophers;
	int				i;
	sem_t			*forks;

	philosophers = malloc(sizeof(*philosophers) * args[NUMBER_OF_PHILOSOPHERS]);
	if (philosophers == NULL)
		return (NULL);
	forks = sem_open(FORKS_SEMAPHORE, O_CREAT, 0660,
			args[NUMBER_OF_PHILOSOPHERS]);
	if (forks == SEM_FAILED)
	{
		free(philosophers);
		return (NULL);
	}
	i = -1;
	while (++i < args[NUMBER_OF_PHILOSOPHERS])
	{
		if (init_philosopher(philosophers + i, args, i + 1, forks) < 0)
			ft_putstr_fd("handle error\n", STDERR_FILENO); // TODO
	}
	return (philosophers);
}

static int	init_philosopher(t_philosopher	*philosopher, const int *args,
				const int id, sem_t *forks)
{
	philosopher->time_to_die_semaphore = sem_open(TIME_TO_DIE_SEMAPHORE,
			O_CREAT, 0660, 1);
	// TODO check if sem_wait(philosopher[0].time_to_die_semaphore);
	// decrements the time_to_die_semaphore of all indexes since they use the
	// same link
	if (philosopher->time_to_die_semaphore == SEM_FAILED)
		return (-1);
	philosopher->id = id;
	philosopher->args = args;
	philosopher->forks = forks;
	return (0);
}
