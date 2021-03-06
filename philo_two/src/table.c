/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 08:53:12 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 08:59:46 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

t_table	*g_table;

int	init_sem(const uint64_t n_forks)
{
	sem_unlink("forks_counter");
	sem_unlink("speak_lock");
	sem_unlink("run_lock");
	sem_unlink("satisfied_event");
	g_table->forks_counter = sem_open("forks_counter",
			SEM_OFLAGS, SEM_PERMS, n_forks);
	g_table->speak_lock = sem_open("speak_lock",
			SEM_OFLAGS, SEM_PERMS, 1);
	g_table->run_lock = sem_open("run_lock",
			SEM_OFLAGS, SEM_PERMS, 1);
	g_table->satisfied_event = sem_open("satisfied_event",
			SEM_OFLAGS, SEM_PERMS, 0);
	if (g_table->forks_counter == SEM_FAILED
		|| g_table->speak_lock == SEM_FAILED
		|| g_table->run_lock == SEM_FAILED
		|| g_table->satisfied_event == SEM_FAILED)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	clear_table(const uint64_t n_philo)
{
	uint64_t	i;
	char		*lock_sem;

	set_semlock_value(g_table->run_lock, &g_table->running, 0);
	i = -1;
	while (++i < n_philo)
	{
		lock_sem = ft_strjoin("philo_lock_", ft_uitoa(i + 1));
		destroy_sem(lock_sem, g_table->philos[i].lock, 0);
		free(lock_sem);
	}
	free(g_table->philos);
	free(g_table);
	return (EXIT_SUCCESS);
}

int	check_table_rules(const t_table_rules rules)
{
	if (rules.die_time < 1 || rules.eat_time < 1 || rules.sleep_time < 1
		|| (rules.has_max_eat && rules.eat_time < 1))
	{
		printf ("Error: null or negatives values are not allowed.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	init_table(const t_table_rules rules, const uint64_t n_philo)
{
	uint64_t	i;

	if (check_table_rules(rules)
		|| !nmalloc((void **)&g_table, 1, sizeof(t_table)))
		return (EXIT_FAILURE);
	g_table->rules = rules;
	if (n_philo > 1
		&& !nmalloc((void **)&g_table->philos, n_philo, sizeof(t_philo)))
		return (EXIT_FAILURE);
	init_sem(n_philo);
	g_table->n_philo = n_philo;
	g_table->running = 1;
	g_table->start_time = get_time();
	i = 0;
	while (i < n_philo)
	{
		create_philo(g_table->philos + i++);
		usleep(50);
	}
	i = 0;
	while (i++ < g_table->n_philo)
		sem_wait(g_table->satisfied_event);
	return (clear_table(n_philo));
}
