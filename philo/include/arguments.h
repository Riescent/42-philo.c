/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:20:35 by vfries            #+#    #+#             */
/*   Updated: 2023/03/16 07:20:36 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGUMENTS_H
# define ARGUMENTS_H

int	check_argument_count(int argc);

int	fill_args(int argc, char **argv, int *args);

enum
{
	NUMBER_OF_PHILOSOPHERS = 0,
	TIME_TO_DIE = 1,
	TIME_TO_EAT = 2,
	TIME_TO_SLEEP = 3,
	NUMBER_OF_TIME_TO_EAT = 4,
};

#endif //ARGUMENTS_H
