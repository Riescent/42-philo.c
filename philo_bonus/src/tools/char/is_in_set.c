/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 02:10:35 by vfries            #+#    #+#             */
/*   Updated: 2023/03/09 02:10:36 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "this_is_not_my_libft.h"

bool	ft_is_in_set(char c, char *set)
{
	if (c == '\0')
		return (false);
	return (ft_strchr(set, c) != NULL);
}
