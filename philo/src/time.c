#include <sys/time.h>
#include <unistd.h>

#include "philosophers.h"

struct timeval	get_current_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time);
}

long long	get_timestamp(const t_philosopher *philosopher,
				const struct timeval current_time)
{
	return((current_time.tv_sec - philosopher->start_time.tv_sec) * 1000LL
		+ (current_time.tv_usec - philosopher->start_time.tv_usec) / 1000);
}

void timeval_add_ms(struct timeval *tv, int n)
{
	tv->tv_usec += n * 1000;
	if (tv->tv_usec >= 1000000)
	{
		tv->tv_sec += tv->tv_usec / 1000000;
		tv->tv_usec %= 1000000;
	}
}

int timeval_compare(const struct timeval t1, const struct timeval t2)
{
	if (t1.tv_sec < t2.tv_sec)
		return (-1);
	if (t1.tv_sec > t2.tv_sec)
		return (1);
	if (t1.tv_usec < t2.tv_usec)
		return (-1);
	if (t1.tv_usec > t2.tv_usec)
		return (1);
	return (0);
}