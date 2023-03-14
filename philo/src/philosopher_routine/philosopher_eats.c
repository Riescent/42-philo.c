#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

#include "tools/ft_colors.h"

#include "arguments.h"
#include "philo_time.h"
#include "philosophers.h"

static bool	take_forks(t_philosopher *philosopher);
static void	print_has_taken_a_fork(t_philosopher *philosopher);
static void	let_go_of_forks(t_philosopher *philosopher);

bool	philosopher_eats(t_philosopher *philosopher)
{
	struct timeval	current_time;
	struct timeval	time_to_eat;

	if (take_forks(philosopher))
		return (philosopher_dies(philosopher));
	current_time = get_current_time();
	time_to_eat = current_time;
	philosopher->time_to_die = current_time;
	timeval_add_ms(&time_to_eat, philosopher->args[TIME_TO_EAT]);
	timeval_add_ms(&philosopher->time_to_die, philosopher->args[TIME_TO_DIE]);
	print_state_change("%lli\t%i "GREEN"is eating\n"COLOR_RESET,
		get_timestamp(philosopher, current_time), philosopher);
	if (timeval_compare(philosopher->time_to_die, current_time) <= 0)
	{
		sleep_till(philosopher->time_to_die, NULL, false);
		philosopher_dies(philosopher);
		let_go_of_forks(philosopher);
		return (true);
	}
	sleep_till(time_to_eat, NULL, false);
	let_go_of_forks(philosopher);
	return (false);
}

static bool	take_forks(t_philosopher *philosopher)
{
	while (true)
	{
		usleep(200);
		if (timeval_compare(philosopher->time_to_die, get_current_time()) <= 0)
			return (philosopher_dies(philosopher));
		pthread_mutex_lock(&philosopher->right_fork_mutex);
		if (philosopher->right_fork)
		{
			pthread_mutex_unlock(&philosopher->right_fork_mutex);
			continue ;
		}
		pthread_mutex_lock(philosopher->left_fork_mutex);
		if (*philosopher->left_fork)
		{
			pthread_mutex_unlock(&philosopher->right_fork_mutex);
			pthread_mutex_unlock(philosopher->left_fork_mutex);
			continue ;
		}
		philosopher->right_fork = true;
		*philosopher->left_fork = true;
		pthread_mutex_unlock(&philosopher->right_fork_mutex);
		pthread_mutex_unlock(philosopher->left_fork_mutex);
		print_has_taken_a_fork(philosopher);
		return (false);
	}
}

static void	print_has_taken_a_fork(t_philosopher *philosopher)
{
	struct timeval	current_time;
	long long		timestamp;

	current_time = get_current_time();
	timestamp = get_timestamp(philosopher, current_time);
	print_state_change("%lli\t%i "YELLOW"has taken a fork\n"COLOR_RESET,
		timestamp, philosopher);
	print_state_change("%lli\t%i "YELLOW"has taken a fork\n"COLOR_RESET,
		timestamp, philosopher);
}

static void	let_go_of_forks(t_philosopher *philosopher)
{
	pthread_mutex_lock(&philosopher->right_fork_mutex);
	pthread_mutex_lock(philosopher->left_fork_mutex);
	philosopher->right_fork = 0;
	*philosopher->left_fork = 0;
	pthread_mutex_unlock(&philosopher->right_fork_mutex);
	pthread_mutex_unlock(philosopher->left_fork_mutex);
}
