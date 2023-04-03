/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_eats.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:16 by vfries            #+#    #+#             */
/*   Updated: 2023/03/16 07:15:16 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

#include "tools/ft_colors.h"

#include "arguments.h"
#include "philo_time.h"
#include "philosophers.h"

static int	take_forks(t_philosopher *philosopher);
static int	print_has_taken_a_fork(t_philosopher *philosopher);
static void	let_go_of_forks(t_philosopher *philosopher);

int	philosopher_eats(t_philosopher *philosopher)
{
	struct timeval	current_time;
	struct timeval	time_to_eat;

	if (take_forks(philosopher))
		return (-1);
	current_time = get_current_time();
	time_to_eat = current_time;
	pthread_mutex_lock(&philosopher->time_to_die_mutex);
	philosopher->time_to_die = current_time;
	timeval_add_ms(&philosopher->time_to_die, philosopher->args[TIME_TO_DIE]);
	pthread_mutex_unlock(&philosopher->time_to_die_mutex);
	timeval_add_ms(&time_to_eat, philosopher->args[TIME_TO_EAT]);
	if (print_state_change("%lli\t%i "GREEN"is eating\n"COLOR_RESET,
		get_timestamp(philosopher, current_time), philosopher) < 0)
		return (-1);
	sleep_till(time_to_eat);
	let_go_of_forks(philosopher);
	return (0);
}

static int	take_forks(t_philosopher *philosopher)
{
	if (philosopher->id % 2)
	{
		pthread_mutex_lock(&philosopher->right_fork_mutex);
		pthread_mutex_lock(philosopher->left_fork_mutex);
	}
	else
	{
		pthread_mutex_lock(philosopher->left_fork_mutex);
		pthread_mutex_lock(&philosopher->right_fork_mutex);
	}
	return (print_has_taken_a_fork(philosopher));
}

static int	print_has_taken_a_fork(t_philosopher *philosopher)
{
	struct timeval	current_time;
	long long		timestamp;

	current_time = get_current_time();
	timestamp = get_timestamp(philosopher, current_time);
	if (print_state_change("%lli\t%i "YELLOW"has taken a fork\n"COLOR_RESET,
		timestamp, philosopher) < 0
		|| print_state_change("%lli\t%i "YELLOW"has taken a fork\n"COLOR_RESET,
		timestamp, philosopher) < 0)
		return (-1);
	return (0);
}

static void	let_go_of_forks(t_philosopher *philosopher)
{
	pthread_mutex_unlock(&philosopher->right_fork_mutex);
	pthread_mutex_unlock(philosopher->left_fork_mutex);
}
