/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 08:50:18 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 08:51:49 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

static void	*philo_routine(void *const arg)
{
	t_philo	*self;

	self = (t_philo *)arg;
	while (!self->satisfied)
	{
		if (philo_take_forks(self) == EXIT_FAILURE)
			return (NULL);
		if (philo_eat(self) == EXIT_FAILURE)
		{
			sem_post(g_table->forks_counter);
			sem_post(g_table->forks_counter);
			return (NULL);
		}
		if (!self->satisfied)
			philo_sleep(self);
	}
	return (arg);
}

static void	*death_observer_routine(void *const arg)
{
	t_philo		*self;
	uint64_t	n_philo;

	self = (t_philo *)arg;
	while (!self->satisfied)
	{
		sem_wait(self->lock);
		if (get_time_since(self->last_eat_time) >= g_table->rules.die_time)
		{
			if (philo_talk(self, A_DIE, 0) == EXIT_FAILURE)
				return (NULL);
			n_philo = g_table->n_philo + 1;
			while (n_philo-- != 0)
				sem_post(g_table->satisfied_event);
			return (NULL);
		}
		if (!self->satisfied && g_table->rules.has_max_eat
			&& self->eat_times == g_table->rules.max_eat)
		{
			self->satisfied = 1;
			sem_post(g_table->satisfied_event);
		}
		sem_post(self->lock);
	}
	return (arg);
}

uint8_t	create_philo(t_philo *const philo)
{
	static uint64_t	philo_id = 0;
	char			*lock_sem;

	philo_id++;
	lock_sem = ft_strjoin("philo_lock_", ft_uitoa(philo_id));
	philo->id = philo_id;
	philo->eat_times = 0;
	philo->birth_time = get_time();
	philo->last_eat_time = philo->birth_time;
	philo->satisfied = 0;
	sem_unlink(lock_sem);
	philo->lock = sem_open(lock_sem, SEM_OFLAGS, SEM_PERMS, 1);
	if (philo->lock == SEM_FAILED)
		return (EXIT_FAILURE);
	free(lock_sem);
	if ((pthread_create(&philo->thread, NULL, philo_routine, philo)) != 0)
		return (EXIT_FAILURE);
	if ((pthread_detach(philo->thread)) != 0)
		return (EXIT_FAILURE);
	if ((pthread_create(&philo->death_observer, NULL,
				death_observer_routine, philo)) != 0)
		return (EXIT_FAILURE);
	if ((pthread_detach(philo->death_observer)) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
