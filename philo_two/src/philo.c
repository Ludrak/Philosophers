
#include "table.h"
#include <unistd.h>

static void *philo_routine(void *const arg)
{
    t_philo *self;

    self = (t_philo *)arg;
    while (g_table->running)
    {
        if (philo_take_forks(self) == EXIT_FAILURE)
            continue ;
        if (philo_eat(self) == EXIT_FAILURE || philo_sleep(self) == EXIT_FAILURE
            || (self->eat_times >= g_table->rules.max_eat_time && g_table->rules.has_max_eat))
            return (NULL);
    }
    return (arg);
}



static void *death_observer_routine(void *const arg)
{
    t_philo *self;

    self = (t_philo *)arg;
    while (g_table->running)
    {
        if (sem_wait(self->lock) != 0)
            return (NULL);
        if (get_time_since(self->last_eat_time) >= g_table->rules.die_time)
        {
            philo_talk(self, A_DIE, 0);
            g_table->running = 0;
            sem_post(self->lock);
            return (NULL);
        }
        if (sem_post(self->lock) != 0)
            return (NULL);
    }
    return (arg);
}



uint8_t     create_philo(t_philo *philo)
{
    static uint64_t     philo_id = 0;
    char                *lock_sem;
    
    philo_id++;
    lock_sem = ft_strjoin("philo_lock_", ft_itoa(philo_id));
    philo->id = philo_id;
    philo->eat_times = 0;
    philo->birth_time = get_time();
    philo->last_eat_time = philo->birth_time;
    sem_unlink(lock_sem);
    if ((philo->lock = sem_open(lock_sem, SEM_OFLAGS, SEM_PERMS, 1)) == SEM_FAILED)
        return (EXIT_FAILURE);
    free(lock_sem);
    if ((pthread_create(&philo->thread, NULL, philo_routine, philo)) != 0)
        return (EXIT_FAILURE);
    if ((pthread_detach(philo->thread)) != 0)
        return (EXIT_FAILURE);
    if ((pthread_create(&philo->death_observer, NULL, death_observer_routine, philo)) != 0)
        return (EXIT_FAILURE);
    if ((pthread_detach(philo->death_observer)) != 0)
        return (EXIT_FAILURE);

    return (EXIT_SUCCESS);
}
