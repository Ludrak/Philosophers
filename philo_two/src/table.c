
#include "table.h"

t_table     *g_table;

int     init_sem(const uint64_t n_forks)
{
    sem_unlink("forks");
    if ((g_table->forks = sem_open("forks", SEM_OFLAGS, SEM_PERMS, n_forks)) == SEM_FAILED)
        return (EXIT_FAILURE);
    sem_unlink("speak_lock");
    if ((g_table->speak_lock = sem_open("speak_lock", SEM_OFLAGS, SEM_PERMS, 1)) == SEM_FAILED)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int     destroy_sem(char *sem_name, sem_t *sem)
{
    if(sem_close(sem) != 0)
        return(EXIT_FAILURE);
    if(sem_unlink(sem_name) != 0)
        return (EXIT_FAILURE);
    return(EXIT_SUCCESS);
}

int     clear_table(uint64_t n_philo)
{
    uint64_t    i;

    i = -1;
    while (++i < n_philo)
        destroy_sem(ft_strjoin("philo_lock_", ft_itoa(i + 1)), g_table->philos[i].lock);
    destroy_sem("forks", g_table->forks);
    destroy_sem("speak_lock", g_table->speak_lock);
    free(g_table->philos);
    free(g_table);
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
    init_sem(n_philo);
    g_table->start_time = get_time();
    g_table->running = 1;
    i = 0;
    while (i < n_philo)
    {
        create_philo(g_table->philos + i++);
        usleep(50);
    }
    while (g_table->running)
        ;
    return (clear_table(n_philo));
}