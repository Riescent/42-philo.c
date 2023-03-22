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

static int	start_all_philosophers(t_philosopher *philosophers,
				sem_t *execution_semaphore);
static void	error_in_run_philosopher(t_philosopher *philosophers,
				int index_at_which_philosopher_initialisation_failed, int size,
				char *error_message);
static void	*kill_all_process_when_one_dies(void *philosophers_void);

void	run_philosopher(t_philosopher *philosophers)
{
	int			size;
	sem_t		*execution_semaphore;
	pthread_t	philosopher_death_checker;

	execution_semaphore = sem_open(EXECUTION_SEMAPHORE, O_CREAT, 0660, 1);
	philosophers->should_kill_all_philosophers = sem_open(
			SHOULD_KILL_ALL_PHILOSOPHERS_SEMAPHORE, O_CREAT, 0660, 0);
	philosophers->philosopher_died = sem_open(PHILOSOPHER_DIED_SEMAPHORE,
			O_CREAT, 0660, 1);
	if (execution_semaphore == SEM_FAILED
		|| philosophers->philosopher_died == SEM_FAILED
		|| philosophers->should_kill_all_philosophers == SEM_FAILED)
	{
		sem_close(execution_semaphore);
		sem_close(philosophers->should_kill_all_philosophers);
		sem_close(philosophers->philosopher_died);
		ft_putstr_fd("Failed to init execution_semaphore or ", STDERR_FILENO);
		ft_putstr_fd("philosopher_died semaphore\n", STDERR_FILENO);
		return ;
	}
	sem_wait(execution_semaphore);
	size = start_all_philosophers(philosophers, execution_semaphore);
	sem_post(execution_semaphore);
	if (size == philosophers->args[NUMBER_OF_PHILOSOPHERS])
	{
		if (pthread_create(&philosopher_death_checker, NULL,
				&kill_all_process_when_one_dies, philosophers) != 0)
		{
			sem_close(execution_semaphore);
			sem_close(philosophers->should_kill_all_philosophers);
			sem_close(philosophers->philosopher_died);
			return (error_in_run_philosopher(philosophers, size, size,
					"Failed to init philosopher_death_checker\n"));
		}
		pthread_detach(philosopher_death_checker);
	}
	while (size--)
		waitpid(philosophers[size].philosopher_pid, NULL, 0);
	sem_close(execution_semaphore);
	sem_close(philosophers->should_kill_all_philosophers);
	sem_close(philosophers->philosopher_died);
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

static void	error_in_run_philosopher(t_philosopher *philosophers,
				int index_at_which_philosopher_initialisation_failed, int size,
				char *error_message)
{
	while (size--)
	{
		if (size < index_at_which_philosopher_initialisation_failed)
			kill(philosophers[size].philosopher_pid, SIGINT);
		philosophers[size].philosopher_pid = -1;
	}
	ft_putstr_fd(error_message, STDERR_FILENO);
}

static void	*kill_all_process_when_one_dies(void *philosophers_void)
{
	int				i;
	t_philosopher	*philosophers;

	philosophers = philosophers_void;
	i = philosophers->args[NUMBER_OF_PHILOSOPHERS];
	sem_wait(philosophers->should_kill_all_philosophers);
	while (i--)
		kill(philosophers[i].philosopher_pid, SIGINT);
	return (NULL);
}
