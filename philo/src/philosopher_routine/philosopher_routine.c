#include <stdio.h>
#include <unistd.h>

#include "ft_colors.h"

#include "philosophers.h"
#include "arguments.h"
#include "philo_time.h"

static bool	no_philosophers_are_dead(t_philosopher *philosopher);

void	*philosopher_routine(void *philosopher_void)
{
	t_philosopher	*philosopher;
	int				nb_of_times_to_eat;

	philosopher = philosopher_void;
	nb_of_times_to_eat = philosopher->args[NUMBER_OF_TIME_TO_EAT];
	while (no_philosophers_are_dead(philosopher))
	{
		if (philosopher_eats(philosopher))
			return (NULL);
		if (--nb_of_times_to_eat == 0)
			return (NULL);
		if (philosopher_sleeps(philosopher))
			return (NULL);
		print_state_change("%lli\t%i "PURPLE"is thinking\n"COLOR_RESET,
			get_timestamp(philosopher, get_current_time()), philosopher);
		usleep(300);
	}
	return (NULL);
}

static bool	no_philosophers_are_dead(t_philosopher *philosopher)
{
	bool	return_value;

	pthread_mutex_lock(philosopher->philosopher_died_mutex);
	return_value = *philosopher->philosopher_died == false;
	pthread_mutex_unlock(philosopher->philosopher_died_mutex);
	return (return_value);
}
