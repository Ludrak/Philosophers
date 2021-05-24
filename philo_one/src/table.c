/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 11:46:09 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 08:39:57 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"

t_table	*g_table;

int	init_mutex(const uint64_t n_forks)
{
	uint64_t	i;

	g_table->forks = (pthread_mutex_t *)
		malloc(sizeof(pthread_mutex_t) * n_forks);
	if (!g_table->forks)
		return (EXIT_FAILURE);
	i = 0;
	while (i < n_forks)
		if (pthread_mutex_init(g_table->forks + i++, NULL) != 0)
			return (EXIT_FAILURE);
	if (pthread_mutex_init(&g_table->speak_lock, NULL) != 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	all_satisfied(void)
{
	uint64_t	satisfied;
	uint8_t		i;

	i = 0;
	satisfied = 0;
	while (i < g_table->n_philo)
		satisfied += g_table->philos[i++].satisfied;
	if (satisfied == g_table->n_philo)
		return (1);
	return (0);
}

int	init_table(const t_table_rules rules, uint64_t n_philo)
{
	uint64_t	i;

	if (!nmalloc((void **)&g_table, 1, sizeof(t_table)) || n_philo <= 1)
		return (EXIT_FAILURE);
	g_table->rules = rules;
	if (!nmalloc((void **)&g_table->philos, n_philo, sizeof(t_philo)))
		return (EXIT_FAILURE);
	g_table->n_philo = n_philo;
	init_mutex(n_philo);
	g_table->start_time = get_time();
	g_table->running = 1;
	i = 0;
	while (i < n_philo)
	{
		g_table->philos[i].forks[0] = g_table->forks + i;
		if (i < n_philo - 1)
			g_table->philos[i].forks[1] = g_table->forks + i + 1;
		else
			g_table->philos[i].forks[1] = g_table->forks;
		create_philo(g_table->philos + i++);
		usleep(50);
	}
	while (g_table->running && (!rules.has_max_eat || !all_satisfied()))
		usleep(50);
	return (EXIT_SUCCESS);
}
