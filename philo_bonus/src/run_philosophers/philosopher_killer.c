#include <pthread.h>
#include <sys/semaphore.h>
#include <signal.h>

#include "arguments.h"
#include "philosophers.h"

static void	*philosopher_killer_routine(void *philosophers_void);

int	init_philosopher_killer(t_philosopher *philosophers, int size,
		sem_t *execution_semaphore)
{
	pthread_t	philosopher_killer;

	if (size != philosophers->args[NUMBER_OF_PHILOSOPHERS])
		return (0);
	if (pthread_create(&philosopher_killer, NULL,
			&philosopher_killer_routine, philosophers) == 0)
	{
		pthread_detach(philosopher_killer);
		return (0);
	}
	sem_close(execution_semaphore);
	sem_close(philosophers->should_kill_all_philosophers);
	sem_close(philosophers->philosopher_died);
	error_in_run_philosopher(philosophers, size, size,
		"Failed to init philosopher_killer\n");
	return (-1);
}

static void	*philosopher_killer_routine(void *philosophers_void)
{
	int				i;
	t_philosopher	*philosophers;

	philosophers = philosophers_void;
	i = philosophers->args[NUMBER_OF_PHILOSOPHERS];
	sem_wait(philosophers->should_kill_all_philosophers);
	while (i--)
		kill(philosophers[i].philosopher_pid, SIGINT);
	return (NULL);
}
