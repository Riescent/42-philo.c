/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:15:00 by vfries            #+#    #+#             */
/*   Updated: 2023/04/10 18:38:00 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <limits.h>

#include "tools.h"

#include "arguments.h"

int	check_argument_count(int argc)
{
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Bad number of arguments:\n", STDERR_FILENO);
		ft_putstr_fd("\t./philo number_of_philosophers time_to_die ",
			STDERR_FILENO);
		ft_putstr_fd("time_to_eat time_to_sleep ", STDERR_FILENO);
		ft_putstr_fd("[number_of_times_each_philosopher_must_eat]\n",
			STDERR_FILENO);
		return (-1);
	}
	return (0);
}

int	fill_args(int argc, char **argv, int *args)
{
	int			i;
	long long	tmp;

	errno = 0;
	i = 0;
	while (++i < argc)
	{
		tmp = ft_atoll(argv[i]);
		if (tmp > INT_MAX || tmp < 1)
		{
			ft_putstr_fd("Inputted arguments can't be above ", STDERR_FILENO);
			ft_putstr_fd("INT_MAX or below 1\n", STDERR_FILENO);
			return (-1);
		}
		args[i - 1] = (int)tmp;
	}
	if (errno == EINVAL)
	{
		ft_putstr_fd("Inputted arguments need to be numbers\n", STDERR_FILENO);
		return (-1);
	}
	if (argc == 5)
		args[NUMBER_OF_TIME_TO_EAT] = INFINITE_EAT;
	return (0);
}
