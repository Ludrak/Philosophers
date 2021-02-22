
#ifndef PHILO_TIME_H
# define PHILO_TIME_H

# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

uint64_t    get_time();
uint64_t	get_time_since(const uint64_t time);
void		sleep_until(const uint64_t time);

#endif