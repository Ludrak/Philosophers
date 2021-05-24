/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 09:34:33 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 09:36:00 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TABLE_H
# define TABLE_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <sys/stat.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>

# include "philo.h"
# include "utils.h"

/*
**	0xa00 corresponds to (O_CREAT | O_EXCL)
**	0x660 corresponds to (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)
*/
# define SEM_OFLAGS			0xa00
# define SEM_PERMS			0x660

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
	sem_t			*speak_lock;
	sem_t			*forks_counter;
	sem_t			*satisfied_event;
	sem_t			*run_lock;
	t_table_rules	rules;
}				t_table;

extern t_table	*g_table;

int		init_table(t_table_rules rules, uint64_t n_philo);

/*
**  SEMLOCK UTILS
*/

uint8_t	get_semlock_value(sem_t *sem_lock, void *locked_value);
void	set_semlock_value(sem_t *sem_lock, void *locked_value, uint8_t value);
int		destroy_sem(const char *const sem_name, sem_t *sem, uint8_t post);

#endif
