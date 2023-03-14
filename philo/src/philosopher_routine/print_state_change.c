#include <stdio.h>

#include "philosophers.h"

void	print_state_change(const char *format, const long long timestamp,
			t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->philosopher_died_mutex);
	if (*philosopher->philosopher_died)
	{
		pthread_mutex_unlock(philosopher->philosopher_died_mutex);
		return ;
	}
	pthread_mutex_unlock(philosopher->philosopher_died_mutex);
	printf(format, timestamp, philosopher->id);
}
