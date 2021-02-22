
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

static uint64_t  count(uint64_t n)
{
	uint64_t		i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char	*ft_itoa(uint64_t n)
{
	char			    *result;
	uint64_t			i;
	uint64_t            nb;

	nb = (n < 0) ? -n : n;
	i = count(n);
	if (!(result = malloc((i + 1) * sizeof(*result))))
		return (0);
    result[i] = 0;
	if (n == 0)
	{
		result[0] = '0';
		return (result);
	}
	while (nb)
	{
		result[--i] = nb % 10 + '0';
		nb /= 10;
	}
	return (result);
}

size_t      ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s && s[i])
        i++;
    return (i);
}

char        *ft_strjoin(char *s1, char *s2)
{
    char    *out;
    char    *s2_buff;
    size_t  out_len;
    int     i;

    i = 0;
    s2_buff = s2;
    out_len = ft_strlen(s1) + ft_strlen(s2) + 1;
    if (!(out = malloc(sizeof(char) * out_len)))
        return (NULL);
    while (s1 && *s1)
        out[i++] = *s1++;
    while(s2 && *s2)
        out[i++] = *s2++;
    out[i] = 0;
    free(s2_buff);
    return (out);
}
