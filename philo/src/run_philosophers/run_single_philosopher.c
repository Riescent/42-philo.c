#include <stdio.h>

#include "tools.h"

#include "arguments.h"
#include "philo_time.h"

static void	*single_philosopher_routine(void *philosopher_void);

void	run_single_philosopher(t_philosopher *philosophers)
{
	pthread_t	philosopher_thread;

	if (pthread_create(&philosopher_thread, NULL, &single_philosopher_routine,
			philosophers) != 0)
	{
		ft_putstr_fd("Failed to create philosopher thread\n",
				STDERR_FILENO);
		return ;
	}
	pthread_join(philosopher_thread, NULL);
}

static void	*single_philosopher_routine(void *philosopher_void)
{
	t_philosopher	*philosopher;

	printf("%i\t%i "YELLOW"has taken a fork\n"COLOR_RESET, 0, 1);
	philosopher = philosopher_void;
	philosopher->time_to_die = get_current_time();
	timeval_add_ms(&philosopher->time_to_die, philosopher->args[TIME_TO_DIE]);
	sleep_till(philosopher->time_to_die, philosopher);
	printf("%i\t%i "RED"died\n"COLOR_RESET, philosopher->args[TIME_TO_DIE], 1);
	return (NULL);
}
