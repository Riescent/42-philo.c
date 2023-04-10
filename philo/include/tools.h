/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 19:22:16 by vfries            #+#    #+#             */
/*   Updated: 2023/04/10 18:52:35 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# define BLACK "\001\e[0;30m\002"
# define BLACK_HIGH_INTENSITY "\001\e[0;90m\002"

# define RED "\001\e[0;31m\002"

# define GREEN "\001\e[0;32m\002"

# define YELLOW "\001\e[0;33m\002"

# define BLUE "\001\e[0;34m\002"
# define BLUE_HIGH_INTENSITY "\001\e[0;94m\002"

# define PURPLE "\001\e[0;35m\002"
# define PURPLE_BOLD "\001\e[1;35m\002"
# define PURPLE_BOLD_HIGH_INTENSITY "\001\e[1;95m\002"

# define CYAN "\001\e[0;36m\002"
# define CYAN_HIGH_INTENSITY "\001\e[0;96m\002"

# define WHITE "\001\e[0;37m\002"

# define COLOR_RESET "\001\e[m\002"

# include <unistd.h>

int			ft_putstr_fd(const char *s, int fd);

int			ft_isspace(int c);
int			ft_isdigit(int c);

long long	ft_atoll(const char *str);

size_t		ft_strlen(const char *msg);

#endif
