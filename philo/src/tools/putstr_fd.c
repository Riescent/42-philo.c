/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:39:01 by vfries            #+#    #+#             */
/*   Updated: 2023/04/10 18:52:44 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"
#include <unistd.h>

int	ft_putstr_fd(const char *s, int fd)
{
	if (s == NULL)
		return (-1);
	return (write(fd, s, ft_strlen(s)));
}
