/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:29:09 by vfries            #+#    #+#             */
/*   Updated: 2023/03/22 15:29:19 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "ft_colors.h"

#include "philo_time.h"

static void	*death_checker(void *philosopher);
static bool	philosopher_is_dead(t_philosopher *philosopher);
static void	kill_philosopher(t_philosopher *philosopher);

int	start_death_checker(t_philosopher *philosopher)
{
	pthread_t	death_checker_thread;

	if (pthread_create(&death_checker_thread, NULL,
			&death_checker, philosopher) != 0)
	{
		sem_wait(philosopher->philosopher_died);
		printf(RED"Failed to start death checker for philosopher %d\n%s",
			philosopher->id, "stopping all philosophers...\n"COLOR_RESET);
		sem_post(philosopher->should_kill_all_philosophers);
		return (-1);
	}
	pthread_detach(death_checker_thread);
	return (0);
}

static void	*death_checker(void *philosopher)
{
	while (true)
	{
		if (philosopher_is_dead(philosopher))
		{
			kill_philosopher(philosopher);
			return (NULL);
		}
		usleep(500);
	}
}

static bool	philosopher_is_dead(t_philosopher *philosopher)
{
	const struct timeval	current_time = get_current_time();
	bool					return_value;

	sem_wait(philosopher->time_to_die_semaphore);
	return_value = timeval_compare(philosopher->time_to_die, current_time) <= 0;
	sem_post(philosopher->time_to_die_semaphore);
	return (return_value);
}

static void	kill_philosopher(t_philosopher *philosopher)
{
	sem_wait(philosopher->philosopher_died);
	printf("%lli\t%i "RED"died\n"COLOR_RESET,
		get_timestamp(philosopher, get_current_time()), philosopher->id);
	sem_post(philosopher->should_kill_all_philosophers);
}
