#include <stdio.h>

#include "ft_colors.h"

#include "philo_time.h"

bool	philosopher_dies(t_philosopher *philosopher)
{
	sem_wait(philosopher->philosopher_died);
	printf("%lli\t%i "RED"died\n"COLOR_RESET,
		get_timestamp(philosopher, get_current_time()), philosopher->id);
	sem_post(philosopher->should_kill_all_philosophers);
	return (true);
}