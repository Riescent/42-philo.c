/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:13 by vfries            #+#    #+#             */
/*   Updated: 2023/03/16 07:15:14 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "ft_colors.h"

#include "philosophers.h"
#include "arguments.h"
#include "philo_time.h"

static void	init_philosopher_routine(t_philosopher *philosopher,
				int *number_of_times_to_eat);
static void	free_everything(t_philosopher *philosopher);
static bool	philosopher_has_eaten_the_asked_amount_of_time(
				int *number_of_times_to_eat);

int	philosopher_routine(t_philosopher *philosopher)
{
	int	number_of_times_to_eat;

	init_philosopher_routine(philosopher, &number_of_times_to_eat);
	if (start_death_checker(philosopher) < 0)
		return (free_everything(philosopher), 2);
	philosopher_eats(philosopher);
	while (philosopher_has_eaten_the_asked_amount_of_time(
		&number_of_times_to_eat) == false)
	{
		philosopher_sleeps(philosopher);
		printf("%lli\t%i "PURPLE"is thinking\n"COLOR_RESET,
			get_timestamp(philosopher, get_current_time()), philosopher->id);
		usleep(300);
		philosopher_eats(philosopher);
	}
	free_everything(philosopher);
	return (0);
}

static void	init_philosopher_routine(t_philosopher *philosopher,
				int *number_of_times_to_eat)
{
	*number_of_times_to_eat = philosopher->args[NUMBER_OF_TIME_TO_EAT];
	sem_wait(philosopher->execution_semaphore);
	sem_post(philosopher->execution_semaphore);
	philosopher->start_time = get_current_time();
	philosopher->time_to_die = philosopher->start_time;
	timeval_add_ms(&philosopher->time_to_die, philosopher->args[TIME_TO_DIE]);
}

static void	free_everything(t_philosopher *philosopher)
{
	destroy_philosophers(philosopher - philosopher->id + 1,
		philosopher->args[NUMBER_OF_PHILOSOPHERS]);
}

static bool	philosopher_has_eaten_the_asked_amount_of_time(
				int *number_of_times_to_eat)
{
	if (*number_of_times_to_eat != -1)
		return (--(*number_of_times_to_eat) == 0);
	return (false);
}
