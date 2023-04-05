/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putendl_fd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:41:36 by vfries            #+#    #+#             */
/*   Updated: 2023/04/05 19:35:20 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <unistd.h>

int	ft_putendl_fd(const char *s, int fd)
{
	int	return_value;

	if (s == NULL)
		return (-1);
	return_value = write(fd, s, ft_strlen(s));
	if (return_value == -1)
		return (-1);
	if (write(fd, "\n", 1) == -1)
		return (-1);
	return (return_value + 1);
}
