/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 09:27:46 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 09:28:11 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

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

void	sleep_until(const uint64_t time)
{
	while (get_time() < time
		&& get_semlock_value(g_table->run_lock, &g_table->running) != 0)
		usleep(500);
}
