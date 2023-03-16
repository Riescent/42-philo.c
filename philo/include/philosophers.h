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

typedef struct s_philosopher
{
	int				id;
	const int		*args;
	bool			right_fork;
	pthread_mutex_t	right_fork_mutex;
	bool			*left_fork;
	pthread_mutex_t	*left_fork_mutex;
	struct timeval	start_time;
	struct timeval	time_to_die;
	bool			*philosopher_died;
	pthread_mutex_t	*philosopher_died_mutex;
	pthread_t		pthread;
	pthread_mutex_t	*execution_lock;
}	t_philosopher;

void			run_philosopher(t_philosopher *philosophers, const int *args);

void			*philosopher_routine(void *philosopher_void);
void			print_state_change(const char *format,
					const long long timestamp, t_philosopher *philosopher);
bool			philosopher_eats(t_philosopher *philosopher);
bool			philosopher_sleeps(t_philosopher *philosopher);
bool			philosopher_dies(t_philosopher *philosopher);
void			sleep_till(const struct timeval goal);

t_philosopher	*init_philosophers(const int *args, bool *philosopher_died,
					pthread_mutex_t	*philosopher_died_mutex);

void			destroy_philosophers(t_philosopher *philosophers, int size);
void			destroy_philosopher(t_philosopher *philosopher);

#endif //PHILOSOPHERS_H
