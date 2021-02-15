
#include "philo.h"

uint64_t     ft_atoi(char *s)
{
    uint64_t    n;
    uint64_t    sign;

    sign = 1;
    n = 0;
    if (*s == '-')
    {
        sign = -1;
        s++;
    }
    while (s && *s >= '0' && *s <= '9')
        n = (n * 10) + (*s++ - '0');
    return (n * sign);
}
