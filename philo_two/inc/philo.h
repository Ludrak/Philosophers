/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 09:06:55 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 09:07:47 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdint.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <fcntl.h>
# include <semaphore.h>

# include "philo_time.h"

# define    A_FORK  0
# define    A_EAT   1
# define    A_SLEEP 2
# define    A_THINK 3
# define    A_DIE   4

# define    EXIT_OVEREAT    3

# define    MAX_THREADS 256

typedef struct s_philo
{
	uint64_t		id;
	uint64_t		birth_time;
	uint64_t		last_eat_time;
	uint64_t		eat_times;
	uint8_t			satisfied;
	pthread_t		thread;
	pthread_t		death_observer;
	sem_t			*lock;
}				t_philo;

uint8_t		create_philo(t_philo *philo);

/*
**  Actions
*/

uint64_t	philo_talk(t_philo *const philo,
				const uint8_t action_id, const uint8_t unlock_speak);
uint8_t		philo_take_forks(t_philo *const philo);
uint8_t		philo_eat(t_philo *const philo);
uint8_t		philo_sleep(t_philo *const philo);

#endif
