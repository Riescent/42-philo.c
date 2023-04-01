#include <signal.h>

#include "this_is_not_my_libft.h"

#include "philosophers.h"

void	error_in_run_philosopher(t_philosopher *philosophers,
			int index_at_which_philosopher_initialisation_failed, int size,
			char *error_message)
{
	while (size--)
	{
		if (size < index_at_which_philosopher_initialisation_failed)
			kill(philosophers[size].philosopher_pid, SIGINT);
		philosophers[size].philosopher_pid = -1;
	}
	ft_putstr_fd(error_message, STDERR_FILENO);
}
