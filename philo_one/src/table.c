
#include "table.h"

t_table     *g_table;

int     init_mutex(const uint64_t n_forks)
{
    uint64_t    i;

    if (!(g_table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * n_forks)))
        return (EXIT_FAILURE);
    i = 0;
    while (i < n_forks)
        if (pthread_mutex_init(g_table->forks + i++, NULL) != 0)
            return (EXIT_FAILURE);
    if (pthread_mutex_init(&g_table->speak_lock, NULL) != 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int     init_table(const t_table_rules rules, uint64_t n_philo)
{
    uint64_t    i;

    if (!(g_table = (t_table *)malloc(sizeof(t_table))))
        return (EXIT_FAILURE);
    g_table->rules = rules;
    if (n_philo > 1 && !(g_table->philos = (t_philo *)malloc(sizeof(t_philo) * n_philo)))
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
    while (g_table->running)
        ;
    return (EXIT_SUCCESS);
}
