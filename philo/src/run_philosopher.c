#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

#include "this_is_not_my_libft.h"

#include "philosophers.h"
#include "philo_time.h"
#include "arguments.h"

static void	set_philosopher_died_to_true_to_stop_all_thread(
				t_philosopher *philosopher);

void	run_philosopher(t_philosopher *philosophers, const int *args)
{
	int 			size;
	int				i;
	struct timeval	current_time;
	struct timeval	time_to_die;
// TODO handle single philosopher
	gettimeofday(&current_time, NULL);
	time_to_die = current_time;
	timeval_add_ms(&time_to_die, args[TIME_TO_DIE]);
	size = args[NUMBER_OF_PHILOSOPHERS];
	i = -1;
	while (++i < size)
	{
		philosophers[i].start_time = current_time;
		philosophers[i].time_to_die = time_to_die;
		if (pthread_create(&philosophers[i].pthread, NULL, &philosopher_routine,
				philosophers + i) != 0)
		{
			set_philosopher_died_to_true_to_stop_all_thread(philosophers);
			printf("Failed to start all threads\n");
			size = i;
			break ;
		}
	}
	while (size--)
		pthread_join(philosophers[size].pthread, NULL);
}

static void	set_philosopher_died_to_true_to_stop_all_thread(
				t_philosopher *philosopher)
{
	pthread_mutex_lock(philosopher->philosopher_died_mutex);
	*philosopher->philosopher_died = true;
	pthread_mutex_unlock(philosopher->philosopher_died_mutex);
}
