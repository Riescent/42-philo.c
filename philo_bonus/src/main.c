/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:14:57 by vfries            #+#    #+#             */
/*   Updated: 2023/03/16 07:14:58 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <sys/semaphore.h>
#include <sys/fcntl.h>
#include <stdlib.h>

#include "this_is_not_my_libft.h"

#include "philosophers.h"
#include "arguments.h"
#include "philosopher_semaphores.h"

void	unlink_all_semaphores(void);

int	main(int argc, char **argv)
{
	int				args[5];
	t_philosopher	*philosophers;

	if (check_argument_count(argc) < 0 || fill_args(argc, argv, args) < 0)
		return (2);
	unlink_all_semaphores();
	philosophers = init_philosophers(args);
	if (philosophers == NULL)
	{
		ft_putstr_fd("init_philosophers() failed\n", STDERR_FILENO);
		unlink_all_semaphores();
		return (3);
	}
	run_philosopher(philosophers);
	destroy_philosophers(philosophers, args[NUMBER_OF_PHILOSOPHERS]);
	unlink_all_semaphores();
	return (0);
}
