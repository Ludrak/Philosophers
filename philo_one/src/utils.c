/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 08:41:32 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 08:41:49 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

uint64_t	ft_atoi(char *s)
{
	uint64_t	n;
	uint64_t	sign;

	sign = 1;
	n = 0;
	if (*s == '-')
		return (0);
	while (s && *s >= '0' && *s <= '9' && n < UINT32_MAX)
		n = (n * 10) + (*s++ - '0');
	if (n >= UINT32_MAX)
		return (UINT32_MAX);
	return (n * sign);
}

uint8_t	ft_isnum(char *s)
{
	if (s && *s == '-')
		s++;
	while (s && *s >= '0' && *s <= '9')
		s++;
	if (*s)
		return (0);
	return (1);
}

void	*nmalloc(void **ptr, size_t size, size_t block)
{
	*ptr = malloc(size * block);
	return (*ptr);
}
