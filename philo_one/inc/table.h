
#ifndef TABLE_H
# define TABLE_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <pthread.h>

# include "philo.h"
# include "utils.h"

typedef struct  s_table_rules
{
    uint16_t        die_time;
    uint16_t        eat_time;
    uint16_t        sleep_time;
    uint16_t        max_eat_time;
}               t_table_rules;

typedef struct  s_table
{
    uint8_t         running;
    uint64_t        start_time;
    uint64_t        n_philo;
    t_philo         *philos;
    pthread_mutex_t speak_lock;
    pthread_mutex_t *forks;
    t_table_rules   rules;
}               t_table;

extern t_table  *g_table;

int     init_table(t_table_rules rules, uint64_t n_philo);

#endif
