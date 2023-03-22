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

static void	take_forks(t_philosopher *philosopher);
static void	let_go_of_forks(t_philosopher *philosopher);

bool	philosopher_eats(t_philosopher *philosopher)
{
	struct timeval	current_time;
	struct timeval	time_to_eat;

	take_forks(philosopher);
	current_time = get_current_time();
	sem_wait(philosopher->time_to_die_semaphore);
	philosopher->time_to_die = current_time;
	timeval_add_ms(&philosopher->time_to_die, philosopher->args[TIME_TO_DIE]);
	sem_post(philosopher->time_to_die_semaphore);
	time_to_eat = current_time;
	timeval_add_ms(&time_to_eat, philosopher->args[TIME_TO_EAT]);
	printf("%lli\t%i "GREEN"is eating\n"COLOR_RESET,
		get_timestamp(philosopher, current_time), philosopher->id);
	sleep_till(time_to_eat);
	let_go_of_forks(philosopher);
	return (false);
}

static void	take_forks(t_philosopher *philosopher)
{
	sem_wait(philosopher->forks);
	printf("%lli\t%i "YELLOW"has taken a fork\n"COLOR_RESET,
		get_timestamp(philosopher, get_current_time()), philosopher->id);
	sem_wait(philosopher->forks);
	printf("%lli\t%i "YELLOW"has taken a fork\n"COLOR_RESET,
		get_timestamp(philosopher, get_current_time()), philosopher->id);
}

static void	let_go_of_forks(t_philosopher *philosopher)
{
	sem_post(philosopher->forks);
	sem_post(philosopher->forks);
}
