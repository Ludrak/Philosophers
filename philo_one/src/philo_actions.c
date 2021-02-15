
#include "table.h"

uint64_t    philo_talk(t_philo *const philo, int action_id)
{
    uint64_t    time;
    static char    *action[5] = {
        "Has taken a fork",
        "Is eating",
        "Is sleeping",
        "Is thinking",
        "died"
    };

    if (pthread_mutex_lock(&g_table->speak_lock) != 0)
        return (EXIT_FAILURE);
    time = get_time();
	if (time < 0)
        time = 0;
    printf ("\033[1;34m%8llu \033[1;32m%2llu \033[1;37m-> \033[3;30m%s\033[0m\n",
        time - g_table->start_time, philo->id, action[action_id]);
    if (pthread_mutex_unlock(&g_table->speak_lock) != 0)
        return (EXIT_FAILURE);
    return (time);
}



uint8_t     philo_take_forks(t_philo *const philo)
{
    if (pthread_mutex_lock(philo->forks[0]) != 0 || philo_talk(philo, A_FORK) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    if (pthread_mutex_lock(philo->forks[1]) != 0 || philo_talk(philo, A_FORK) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}



uint8_t     philo_eat(t_philo *const philo)
{
    if (pthread_mutex_lock(philo->lock) != 0)
        return (EXIT_FAILURE);
    philo->last_eat_time = philo_talk(philo, A_EAT);
    if (pthread_mutex_unlock(philo->lock) != 0)
        return (EXIT_FAILURE);
    sleep_until(philo->last_eat_time + g_table->rules.eat_time);
    if (pthread_mutex_unlock(philo->forks[0]) != 0 || pthread_mutex_unlock(philo->forks[1]) != 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}



uint8_t     philo_sleep(t_philo *const philo)
{
    sleep_until(philo_talk(philo, A_SLEEP) + g_table->rules.sleep_time);
    philo_talk(philo, A_THINK);
    return (EXIT_SUCCESS);
}
