#include "ft_colors.h"

#include "philosophers.h"
#include "philo_time.h"

bool	philosopher_dies(t_philosopher *philosopher)
{
	print_state_change("%lli\t%i "RED"died\n"COLOR_RESET,
		get_timestamp(philosopher, get_current_time()), philosopher);
	pthread_mutex_lock(philosopher->philosopher_died_mutex);
	*philosopher->philosopher_died = true;
	pthread_mutex_unlock(philosopher->philosopher_died_mutex);
	return (true);
}