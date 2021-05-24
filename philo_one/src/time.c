/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 08:40:22 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 08:41:17 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_time.h"

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * (uint64_t)1000 + tv.tv_usec / 1000.0);
}

uint64_t	get_time_since(const uint64_t time)
{
	uint64_t	t;

	t = get_time() - time;
	if (t < 0)
		return (0);
	return (t);
}

void	sleep_until(const uint64_t	time)
{
	while (get_time() < time)
		usleep(500);
}
