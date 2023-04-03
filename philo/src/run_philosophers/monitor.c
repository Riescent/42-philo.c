#include <stdio.h>

#include "this_is_not_my_libft.h"

#include "arguments.h"
#include "philo_time.h"

static void	*monitor_routine(void *philosophers_void);
static bool	handle_philosopher_death(t_philosopher *philosophers);
static bool	is_philosopher_dead(t_philosopher *philosopher);
static void	stop_philosophers(t_philosopher *philosopher);

void	start_monitoring(t_philosopher *philosophers)
{
	pthread_t		monitor;
	int 			size;

	if (pthread_create(&monitor, NULL, &monitor_routine, philosophers) != 0)
	{
		stop_philosophers(philosophers);
		ft_putstr_fd("Failed to create monitor thread\n", STDERR_FILENO);
		return ;
	}
	pthread_mutex_unlock(philosophers->execution_lock);
	pthread_join(monitor, NULL);
	size = philosophers->args[NUMBER_OF_PHILOSOPHERS];
	while (size--)
	{
		pthread_join(philosophers[size].pthread, NULL);
		if (philosophers[size].right_fork_is_locked)
			pthread_mutex_unlock(&philosophers[size].right_fork_mutex);
	}
}

static void	*monitor_routine(void *philosophers_void)
{
	const t_philosopher	*philosophers = philosophers_void;
	struct timeval	tmp;

	tmp = get_current_time();
	if (philosophers->args[TIME_TO_EAT] < philosophers->args[TIME_TO_DIE])
		timeval_add_ms(&tmp, philosophers->args[TIME_TO_EAT] / 2);
	else
		timeval_add_ms(&tmp, philosophers->args[TIME_TO_DIE] / 2);
	sleep_till(tmp);
	while (true)
		if (handle_philosopher_death(philosophers_void))
			return (NULL);
}

static bool	handle_philosopher_death(t_philosopher *philosophers)
{
	int	i;
	int	times_to_eat_remaining;

	times_to_eat_remaining = 0;
	i = philosophers->args[NUMBER_OF_PHILOSOPHERS];
	while (i--)
	{
		if (is_philosopher_dead(philosophers + i))
		{
			stop_philosophers(philosophers + i);
			printf("%lli\t%i "RED"died\n"COLOR_RESET,
					get_timestamp(philosophers + i, get_current_time()),
					philosophers[i].id);
			return (true);
		}
		pthread_mutex_lock(&philosophers[i].nb_of_times_to_eat_mutex);
		times_to_eat_remaining += philosophers[i].nb_of_times_to_eat; // TODO could overflow
		pthread_mutex_unlock(&philosophers[i].nb_of_times_to_eat_mutex);
	}
	if (times_to_eat_remaining == 0)
	{
		stop_philosophers(philosophers + i);
		return (true);
	}
	return (false);
}

static bool	is_philosopher_dead(t_philosopher *philosopher)
{
	const struct timeval	current_time = get_current_time();
	bool					return_value;

	pthread_mutex_lock(&philosopher->time_to_die_mutex);
	return_value = timeval_compare(philosopher->time_to_die, current_time) <= 0;
	pthread_mutex_unlock(&philosopher->time_to_die_mutex);
	return (return_value);
}

static void	stop_philosophers(t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->philosopher_died_mutex);
	*philosopher->philosopher_died = true;
	pthread_mutex_unlock(philosopher->philosopher_died_mutex);
}
