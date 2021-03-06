/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 08:45:20 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 08:45:29 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <pthread.h>

# include "philo.h"
# include "utils.h"

typedef struct s_table_rules
{
	uint32_t		die_time;
	uint32_t		eat_time;
	uint32_t		sleep_time;
	uint32_t		max_eat;
	uint8_t			has_max_eat;
}				t_table_rules;

typedef struct s_table
{
	uint8_t			running;
	uint64_t		start_time;
	uint64_t		n_philo;
	t_philo			*philos;
	pthread_mutex_t	speak_lock;
	pthread_mutex_t	*forks;
	t_table_rules	rules;
}				t_table;

extern t_table	*g_table;

int	init_table(t_table_rules rules, uint64_t n_philo);

#endif
