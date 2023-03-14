#include <pthread.h>
#include "this_is_not_my_libft.h"

#include "philosophers.h"
#include "arguments.h"

int	main(int argc, char **argv)
{
	int				args[5];
	t_philosopher 	*philosophers;
	bool			philosopher_died;
	pthread_mutex_t	philosopher_died_mutex;

	philosopher_died = false;
	if (pthread_mutex_init(&philosopher_died_mutex, NULL) != 0)
		return (ft_putstr_fd("Failed to init philosopher_died_mutex\n",
				STDERR_FILENO), 1);
	if (check_argument_count(argc) < 0 || fill_args(argc, argv, args) < 0)
		return (2);
	philosophers = init_philosophers(args, &philosopher_died,
			&philosopher_died_mutex);
	if (philosophers == NULL)
	{
		ft_putstr_fd("init_philosophers() failed\n", STDERR_FILENO);
		return (3);
	}
	run_philosopher(philosophers, args);
	destroy_philosophers(philosophers, args[NUMBER_OF_PHILOSOPHERS]);
	pthread_mutex_destroy(&philosopher_died_mutex);
	return (0);
}
