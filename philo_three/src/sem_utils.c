/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 09:21:46 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 09:22:22 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

uint8_t	get_semlock_value(sem_t *sem_lock, void *locked_value)
{
	uint8_t	value;

	sem_wait(sem_lock);
	value = *(uint8_t *)locked_value;
	sem_post(sem_lock);
	return (value);
}

void	set_semlock_value(sem_t *sem_lock, void *locked_value, uint8_t value)
{
	sem_wait(sem_lock);
	*(uint8_t *)locked_value = value;
	sem_post(sem_lock);
}

int	destroy_sem(const char *const sem_name, sem_t *sem, uint8_t post)
{
	while (post-- > 0 && sem_post(sem) == 0)
		;
	if (sem_unlink(sem_name) != 0)
		return (EXIT_FAILURE);
	if (sem_close(sem) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
