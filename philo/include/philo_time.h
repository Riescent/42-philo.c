#ifndef PHILO_TIME_H
# define PHILO_TIME_H

# include <sys/time.h>

# include "philosophers.h"

struct timeval	get_current_time(void);
long long		get_timestamp(const t_philosopher *philosopher,
					const struct timeval current_time);
void			sleep_till(const struct timeval goal);
void 			timeval_add_ms(struct timeval *tv, int n);
int				timeval_compare(const struct timeval t1,
					const struct timeval t2);

#endif //PHILO_TIME_H
