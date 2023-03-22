/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_semaphores.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 15:24:44 by vfries            #+#    #+#             */
/*   Updated: 2023/03/22 15:24:44 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_SEMAPHORES_H
# define PHILOSOPHER_SEMAPHORES_H

# define FORKS_SEMAPHORE "forks"
# define EXECUTION_SEMAPHORE "execution_semaphore"
# define PHILOSOPHER_DIED_SEMAPHORE "philosopher_died"
# define SHOULD_KILL_ALL_PHILOSOPHERS_SEMAPHORE "should_kill_all_philosophers"
# define TIME_TO_DIE_SEMAPHORE "time_to_die"

void	unlink_all_semaphores(void);

#endif //PHILOSOPHER_SEMAPHORES_H
