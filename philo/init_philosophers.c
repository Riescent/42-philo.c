#include <stdlib.h>
#include <pthread.h>

#include "this_is_not_my_libft.h"
#include "philosophers.h"

static int	init_philosopher(t_philosopher	*philosopher, const int args[5],
				int id, pthread_mutex_t *print_mutex);
static void	init_left_forks(t_philosopher *philosophers);

t_philosopher	*init_philosophers(const int args[5],
					pthread_mutex_t *print_mutex)
{
	t_philosopher	*philosophers;
	int 			i;

	philosophers = malloc(sizeof(*philosophers) * args[0]);
	if (philosophers == NULL)
		return (NULL);
	i = -1;
	while (++i < args[0])
	{
		if (init_philosopher(philosophers + i, args, i + 1, print_mutex) < 0)
		{
			philosophers->number_of_philosophers = i;
			destroy_philosophers(philosophers);
			return (NULL);
		}
	}
	init_left_forks(philosophers);
	return (philosophers);
}

static int	init_philosopher(t_philosopher	*philosopher, const int args[5],
				const int id, pthread_mutex_t *print_mutex)
{
	if (pthread_mutex_init(&philosopher->thread_should_stop_mutex, NULL) != 0
		|| pthread_mutex_init(&philosopher->right_fork_mutex, NULL) != 0)
	{
		destroy_philosopher(philosopher);
		return (-1);
	}
	philosopher->thread_should_stop = false;
	philosopher->print_mutex = print_mutex;
	philosopher->id = id;
	philosopher->number_of_philosophers = args[0];
	philosopher->time_to_die = args[1];
	philosopher->time_to_eat = args[2];
	philosopher->time_to_sleep = args[3];
	philosopher->number_of_times_to_eat = args[4];
	philosopher->times_eaten = 0;
	philosopher->right_fork = false;
	return (0);
}

static void	init_left_forks(t_philosopher *philosophers)
{
	const int	last = philosophers->number_of_philosophers - 1;
	int			i;

	i = -1;
	while (++i < last)
	{
		philosophers[i + 1].left_fork_mutex = &philosophers[i].right_fork_mutex;
		philosophers[i + 1].left_fork = &philosophers[i].right_fork;
	}
	philosophers[0].left_fork_mutex = &philosophers[i].right_fork_mutex;
	philosophers[0].left_fork = &philosophers[i].right_fork;
}
