/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfries <vfries@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 07:20:28 by vfries            #+#    #+#             */
/*   Updated: 2023/03/16 07:20:29 by vfries           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <sys/semaphore.h>
# include <unistd.h>

typedef struct s_philosopher
{
	int				id;
	const int		*args;
	sem_t			*forks;
	struct timeval	start_time;
	struct timeval	time_to_die;
	sem_t			*time_to_die_semaphore;
	pid_t			philosopher_pid;
	sem_t			*execution_semaphore;
	sem_t			*should_kill_all_philosophers;
	sem_t			*philosopher_died;
}	t_philosopher;

void			error_in_run_philosopher(t_philosopher *philosophers,
					int index_at_which_philosopher_initialisation_failed,
					int size, char *error_message);
int				init_philosopher_killer(t_philosopher *philosophers, int size,
					sem_t *execution_semaphore);
void			run_philosopher(t_philosopher *philosophers);

int				start_death_checker(t_philosopher *philosopher);
int				philosopher_routine(t_philosopher *philosopher);
bool			philosopher_eats(t_philosopher *philosopher);
bool			philosopher_sleeps(t_philosopher *philosopher);
void			sleep_till(const struct timeval goal);

t_philosopher	*init_philosophers(const int *args);

void			destroy_philosophers(t_philosopher *philosophers, int size);
void			destroy_philosopher(t_philosopher *philosopher);

#endif //PHILOSOPHERS_H
