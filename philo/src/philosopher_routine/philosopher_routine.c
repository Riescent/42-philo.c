#include <stdio.h>

#include "ft_colors.h"

#include "philosophers.h"
#include "arguments.h"
#include "philo_time.h"

static bool	no_philosophers_are_dead(t_philosopher *philosopher);
static bool	philosopher_state_changes(t_philosopher *philosopher);

void	*philosopher_routine(void *philosopher_void)
{
	t_philosopher	*philosopher;
	int				nb_of_times_to_eat;

	philosopher = philosopher_void;
	nb_of_times_to_eat = philosopher->args[NUMBER_OF_TIME_TO_EAT];
	while (nb_of_times_to_eat-- && no_philosophers_are_dead(philosopher))
	{
		if (philosopher_state_changes(philosopher))
			return (NULL);
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

static bool	philosopher_state_changes(t_philosopher *philosopher)
{
	if (philosopher_eats(philosopher))
		return (true);
	if (philosopher_sleeps(philosopher))
		return (true);
	print_state_change("%lli\t%i "PURPLE"is thinking\n"COLOR_RESET,
		get_timestamp(philosopher, get_current_time()), philosopher);
	return (false);
}
