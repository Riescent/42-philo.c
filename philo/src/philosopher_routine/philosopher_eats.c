/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_eats.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:16 by vfries            #+#    #+#             */
/*   Updated: 2023/04/10 18:38:27 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

#include "tools.h"

#include "arguments.h"
#include "philo_time.h"
#include "philosophers.h"

static int	take_forks(t_philosopher *philosopher);
static int	take_fork(t_philosopher *philosopher, pthread_mutex_t *fork_mutex);
static void	update_time_to_death_and_time_to_eat(t_philosopher *philosopher,
				struct timeval *time_to_eat);
static void	let_go_of_forks(t_philosopher *philosopher);

int	philosopher_eats(t_philosopher *philosopher)
{
	struct timeval	time_to_eat;

	if (take_forks(philosopher))
		return (-1);
	update_time_to_death_and_time_to_eat(philosopher, &time_to_eat);
	if (print_state_change("%lli\t%i "GREEN"is eating\n"COLOR_RESET,
			philosopher) < 0)
	{
		let_go_of_forks(philosopher);
		return (-1);
	}
	if (philosopher->args[NUMBER_OF_TIME_TO_EAT] != -1)
	{
		pthread_mutex_lock(&philosopher->nb_of_times_to_eat_mutex);
		if (philosopher->nb_of_times_to_eat > 0)
			philosopher->nb_of_times_to_eat--;
		pthread_mutex_unlock(&philosopher->nb_of_times_to_eat_mutex);
	}
	sleep_till(time_to_eat, philosopher);
	let_go_of_forks(philosopher);
	return (0);
}

static int	take_forks(t_philosopher *philosopher)
{
	if (philosopher->id % 2)
	{
		if (take_fork(philosopher, &philosopher->right_fork_mutex) < 0)
			return (-1);
		if (take_fork(philosopher, philosopher->left_fork_mutex) < 0)
		{
			pthread_mutex_unlock(&philosopher->right_fork_mutex);
			return (-1);
		}
	}
	else
	{
		if (take_fork(philosopher, philosopher->left_fork_mutex) < 0)
			return (-1);
		if (take_fork(philosopher, &philosopher->right_fork_mutex) < 0)
		{
			pthread_mutex_unlock(philosopher->left_fork_mutex);
			return (-1);
		}
	}
	return (0);
}

static int	take_fork(t_philosopher *philosopher, pthread_mutex_t *fork_mutex)
{
	pthread_mutex_lock(fork_mutex);
	if (print_state_change(
			"%lli\t%i "YELLOW"has taken a fork\n"COLOR_RESET, philosopher) < 0)
	{
		pthread_mutex_unlock(fork_mutex);
		return (-1);
	}
	return (0);
}

static void	update_time_to_death_and_time_to_eat(t_philosopher *philosopher,
				struct timeval *time_to_eat)
{
	struct timeval	current_time;

	current_time = get_current_time();
	*time_to_eat = current_time;
	pthread_mutex_lock(&philosopher->time_to_die_mutex);
	philosopher->time_to_die = current_time;
	timeval_add_ms(&philosopher->time_to_die, philosopher->args[TIME_TO_DIE]);
	pthread_mutex_unlock(&philosopher->time_to_die_mutex);
	timeval_add_ms(time_to_eat, philosopher->args[TIME_TO_EAT]);
}

static void	let_go_of_forks(t_philosopher *philosopher)
{
	pthread_mutex_unlock(&philosopher->right_fork_mutex);
	pthread_mutex_unlock(philosopher->left_fork_mutex);
}
