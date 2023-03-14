#include <stdio.h>

#include "ft_colors.h"

#include "philosophers.h"
#include "philo_time.h"
#include "arguments.h"

bool	philosopher_sleeps(t_philosopher *philosopher)
{
	struct timeval	current_time;
	struct timeval	time_to_sleep;

	gettimeofday(&current_time, NULL);
	print_state_change("%lli\t%i "BLACK_HIGH_INTENSITY"is sleeping\n"COLOR_RESET,
			get_timestamp(philosopher, current_time), philosopher);
	time_to_sleep = current_time;
	timeval_add_ms(&time_to_sleep, philosopher->args[TIME_TO_SLEEP]);
	if (timeval_compare(philosopher->time_to_die, time_to_sleep) <= 0)
	{
		sleep_till(philosopher->time_to_die, NULL, false);
		return (philosopher_dies(philosopher));
	}
	sleep_till(time_to_sleep, philosopher->args, true);
	return (false);
}
