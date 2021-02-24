
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

# define SEM_OFLAGS			O_CREAT | O_EXCL
# define SEM_PERMS			420

typedef struct  s_table_rules
{
    uint16_t        die_time;
    uint16_t        eat_time;
    uint16_t        sleep_time;
    uint16_t        max_eat;
    uint8_t         has_max_eat;
}               t_table_rules;

typedef struct  s_table
{
    uint8_t         running;
    uint64_t        start_time;
    uint64_t        n_philo;
    t_philo         *philos;
    sem_t           *speak_lock;
    sem_t           *forks_counter;
    sem_t           *satisfied_event;

    sem_t           *run_lock;
    t_table_rules   rules;
}               t_table;

extern t_table  *g_table;

int     init_table(t_table_rules rules, uint64_t n_philo);

/*
**  SEMLOCK UTILS
*/

uint8_t get_semlock_value(sem_t * sem_lock, void *locked_value);
void    set_semlock_value(sem_t * sem_lock, void * locked_value, uint8_t value);

#endif
