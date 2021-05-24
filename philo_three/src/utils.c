/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 09:29:32 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 09:32:10 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "utils.h"

uint64_t	ft_atoui(const char *s)
{
	uint64_t	n;

	n = 0;
	if (*s == '-')
		return (0);
	while (s && *s >= '0' && *s <= '9' && n < UINT32_MAX)
		n = (n * 10) + (*s++ - '0');
	if (n > UINT32_MAX)
		return (UINT32_MAX);
	return (n);
}

static uint64_t	count(uint64_t n)
{
	uint64_t	i;

	i = 1;
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_uitoa(const uint64_t n)
{
	char				*result;
	uint64_t			i;
	uint64_t			nb;

	nb = n;
	if (n < 0)
		nb = -n;
	i = count(n);
	if (!(nmalloc((void **)&result, i + 1, sizeof(*result))))
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

size_t	ft_strlen(const char *const s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, char *s2)
{
	char		*out;
	char		*s2_buff;
	size_t		out_len;
	uint16_t	i;

	i = 0;
	s2_buff = s2;
	out_len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if (!(nmalloc((void **)&out, out_len, sizeof(char))))
		return (NULL);
	while (s1 && *s1)
		out[i++] = *s1++;
	while (s2 && *s2)
		out[i++] = *s2++;
	out[i] = 0;
	free(s2_buff);
	return (out);
}
