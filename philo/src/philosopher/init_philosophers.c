#include <stdlib.h>
#include <pthread.h>

#include "this_is_not_my_libft.h"

#include "philosophers.h"
#include "arguments.h"

static int	init_philosopher(t_philosopher	*philosopher, const int *args,
				const int id);
static void	init_left_forks_and_philosopher_died(t_philosopher *philosophers,
				bool *philosopher_died,
				pthread_mutex_t	*philosopher_died_mutex,
				const int last_philosopher_index);

t_philosopher	*init_philosophers(const int *args, bool *philosopher_died,
					pthread_mutex_t	*philosopher_died_mutex)
{
	t_philosopher	*philosophers;
	int 			i;

	philosophers = malloc(sizeof(*philosophers) * args[0]);
	if (philosophers == NULL)
		return (NULL);
	i = -1;
	while (++i < args[0])
	{
		if (init_philosopher(philosophers + i, args, i + 1) < 0)
		{
			destroy_philosophers(philosophers, i);
			return (NULL);
		}
	}
	init_left_forks_and_philosopher_died(philosophers, philosopher_died,
		philosopher_died_mutex, args[NUMBER_OF_PHILOSOPHERS] - 1);
	return (philosophers);
}

static int	init_philosopher(t_philosopher	*philosopher, const int *args,
				const int id)
{
	if (pthread_mutex_init(&philosopher->right_fork_mutex, NULL) != 0)
	{
		destroy_philosopher(philosopher);
		return (-1);
	}
	philosopher->id = id;
	philosopher->args = args;
	philosopher->right_fork = false;
	return (0);
}

static void	init_left_forks_and_philosopher_died(t_philosopher *philosophers,
				bool *philosopher_died, pthread_mutex_t	*philosopher_died_mutex,
				const int last_philosopher_index)
{
	int			i;

	i = -1;
	while (++i < last_philosopher_index)
	{
		philosophers[i].philosopher_died = philosopher_died;
		philosophers[i].philosopher_died_mutex = philosopher_died_mutex;
		philosophers[i + 1].left_fork_mutex = &philosophers[i].right_fork_mutex;
		philosophers[i + 1].left_fork = &philosophers[i].right_fork;
	}
	philosophers[last_philosopher_index].philosopher_died = philosopher_died;
	philosophers[last_philosopher_index].philosopher_died_mutex
		= philosopher_died_mutex;
	philosophers[0].left_fork_mutex = &philosophers[i].right_fork_mutex;
	philosophers[0].left_fork = &philosophers[i].right_fork;
}
