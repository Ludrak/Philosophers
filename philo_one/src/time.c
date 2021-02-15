
#include "philo_time.h"

uint64_t    get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * (uint64_t)1000 + tv.tv_usec / 1000.0);
}



uint64_t	get_time_since(const uint64_t time)
{
	uint64_t	t;

	t = get_time() - time;
	return (t < 0 ? 0 : t);
}



void		sleep_until(const uint64_t	time)
{
	while(get_time() < time)
		usleep(500);
}
