#include <sys/time.h>
#include <unistd.h>
#include <stdbool.h>

#include "arguments.h"
#include "philo_time.h"

//static long long	adjust_time_to_usleep(long long time_to_usleep,
//						const int multiplier);
#include <stdio.h>
void	sleep_till(const struct timeval goal, const int *args,
			const bool philosopher_is_sleeping)
{
	struct timeval	current_time;
	long long		time_to_usleep;

	t_philosopher	test; // Test

	current_time = get_current_time();
	test.start_time = current_time;	// Test
	time_to_usleep = (long long)(goal.tv_sec - current_time.tv_sec)
		* NB_OF_USECONDS_IN_A_SECOND + (goal.tv_usec - current_time.tv_usec);
//	if (philosopher_is_sleeping)
//		time_to_usleep = adjust_time_to_usleep(time_to_usleep,
//				(args[TIME_TO_EAT] + args[TIME_TO_SLEEP]) * 1000);
	(void)args; (void)philosopher_is_sleeping;
//	usleep(time_to_usleep * (time_to_usleep > 0));
	usleep(200 * NB_OF_USECONDS_IN_A_MILLISECOND);
	(void)time_to_usleep;
	printf("Slept for %lld ms\n", get_timestamp(&test, get_current_time())); // Test
}

//static long long	adjust_time_to_usleep(long long time_to_usleep,
//						const int multiplier)
//{
//	if (multiplier > time_to_usleep)
//		return (time_to_usleep);
//	time_to_usleep += multiplier / 2;
//	time_to_usleep -= time_to_usleep % multiplier;
//	return (time_to_usleep);
//}
