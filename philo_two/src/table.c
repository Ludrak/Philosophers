
#include "table.h"

t_table     *g_table;

int     init_sem(const uint64_t n_forks)
{
    sem_unlink("forks");
    if ((g_table->forks_counter = sem_open("forks", SEM_OFLAGS, SEM_PERMS, n_forks)) == SEM_FAILED)
        return (EXIT_FAILURE);
    sem_unlink("speak_lock");
    if ((g_table->speak_lock = sem_open("speak_lock", SEM_OFLAGS, SEM_PERMS, 1)) == SEM_FAILED)
        return (EXIT_FAILURE);
    sem_unlink("run_lock");
    if ((g_table->run_lock = sem_open("run_lock", SEM_OFLAGS, SEM_PERMS, 1)) == SEM_FAILED)
        return (EXIT_FAILURE);
    sem_unlink("satisfied_event");
    if ((g_table->satisfied_event = sem_open("satisfied_event", SEM_OFLAGS, SEM_PERMS, 0)) == SEM_FAILED)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}

int     destroy_sem(char *sem_name, sem_t *sem, uint8_t post)
{
    if(post && sem_post(sem) != 0)
            return (EXIT_FAILURE);
    if(sem_close(sem) != 0)
        return(EXIT_FAILURE);
    if(sem_unlink(sem_name) != 0)
        return (EXIT_FAILURE);
    return(EXIT_SUCCESS);
}

int     clear_table(uint64_t n_philo)
{
    uint64_t    i;

    set_semlock_value(g_table->run_lock, &g_table->running, 0);
    i = -1;
    while (++i < n_philo)
        destroy_sem(ft_strjoin("philo_lock_", ft_itoa(i + 1)), g_table->philos[i].lock, 0);
    destroy_sem("forks", g_table->forks_counter, 0);
    destroy_sem("speak_lock", g_table->speak_lock, 1);
    destroy_sem("run_lock", g_table->run_lock, 0);
    destroy_sem("satisfied_event", g_table->satisfied_event, 0);
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
    i = 1;
    while(i++ < g_table->n_philo)
    {
        sem_wait(g_table->satisfied_event);
        usleep(10000);
    }     
    return (clear_table(n_philo));
}