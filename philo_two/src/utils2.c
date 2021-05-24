/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 08:09:27 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 09:05:53 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
