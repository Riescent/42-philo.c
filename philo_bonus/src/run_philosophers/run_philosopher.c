/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philosopher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:14:55 by vfries            #+#    #+#             */
/*   Updated: 2023/03/22 15:25:09 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>

#include "this_is_not_my_libft.h"

#include "philosophers.h"
#include "philosopher_semaphores.h"
#include "arguments.h"
#include "philo_time.h"

static int	init_semaphores(sem_t **execution_semaphore,
				t_philosopher *philosophers);
static int	start_all_philosophers(t_philosopher *philosophers,
				sem_t *execution_semaphore);

void	run_philosopher(t_philosopher *philosophers)
{
	int			size;
	sem_t		*execution_semaphore;

	if (init_semaphores(&execution_semaphore, philosophers) < 0)
		return ;
	size = start_all_philosophers(philosophers, execution_semaphore);
	sem_post(execution_semaphore);
	if (init_philosopher_killer(philosophers, size, execution_semaphore) < 0)
		return ;
	while (size--)
		waitpid(philosophers[size].philosopher_pid, NULL, 0);
	sem_close(execution_semaphore);
	sem_close(philosophers->should_kill_all_philosophers);
	sem_close(philosophers->philosopher_died);
}

static int	init_semaphores(sem_t **execution_semaphore,
				t_philosopher *philosophers)
{
	*execution_semaphore = sem_open(EXECUTION_SEMAPHORE, O_CREAT, 0660, 0);
	philosophers->should_kill_all_philosophers = sem_open(
			SHOULD_KILL_ALL_PHILOSOPHERS_SEMAPHORE, O_CREAT, 0660, 0);
	philosophers->philosopher_died = sem_open(PHILOSOPHER_DIED_SEMAPHORE,
			O_CREAT, 0660, 1);
	if (*execution_semaphore == SEM_FAILED
		|| philosophers->philosopher_died == SEM_FAILED
		|| philosophers->should_kill_all_philosophers == SEM_FAILED)
	{
		sem_close(*execution_semaphore);
		sem_close(philosophers->should_kill_all_philosophers);
		sem_close(philosophers->philosopher_died);
		ft_putstr_fd("Failed to init a semaphore\n", STDERR_FILENO);
		return (-1);
	}
	return (0);
}

static int	start_all_philosophers(t_philosopher *philosophers,
				sem_t *execution_semaphore)
{
	int		i;

	i = -1;
	while (++i < philosophers->args[NUMBER_OF_PHILOSOPHERS])
	{
		philosophers[i].execution_semaphore = execution_semaphore;
		philosophers[i].should_kill_all_philosophers
			= philosophers->should_kill_all_philosophers;
		philosophers[i].philosopher_died = philosophers->philosopher_died;
		philosophers[i].philosopher_pid = fork();
		if (philosophers[i].philosopher_pid == -1)
		{
			error_in_run_philosopher(philosophers, i,
				philosophers->args[NUMBER_OF_PHILOSOPHERS],
				"Failed to start all threads\n");
			return (i);
		}
		if (philosophers[i].philosopher_pid == 0)
			exit(philosopher_routine(philosophers + i));
	}
	return (philosophers->args[NUMBER_OF_PHILOSOPHERS]);
}
