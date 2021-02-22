
#include "table.h"

uint64_t    philo_talk(t_philo *const philo, const uint8_t action_id, const uint8_t unlock_speak)
{
    uint64_t        time;
    static char     *action[5] = {
        "Has taken a fork",
        "Is eating",
        "Is sleeping",
        "Is thinking",
        "died"
    };

    if (sem_wait(g_table->speak_lock) != 0)
        return (EXIT_FAILURE);
    time = get_time();
	if (time < 0)
        time = 0;
    printf ("\033[1;34m%8llu \033[1;32m%2llu \033[1;37m-> \033[3;30m%s\033[0m\n",
        time - g_table->start_time, philo->id, action[action_id]);
    if (unlock_speak && sem_post(g_table->speak_lock) != 0)
        return (EXIT_FAILURE);
    return (time);
}



uint8_t     philo_take_forks(t_philo *const philo)
{
    if (sem_wait(g_table->forks) != 0 || philo_talk(philo, A_FORK, 1) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    if (sem_wait(g_table->forks) != 0 || philo_talk(philo, A_FORK, 1) == EXIT_FAILURE)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}



uint8_t     philo_eat(t_philo *const philo)
{
    if (sem_wait(philo->lock) != 0)
        return (EXIT_FAILURE);
    philo->last_eat_time = philo_talk(philo, A_EAT, 1);
    if (g_table->rules.has_max_eat)
       philo->eat_times++;
    if (sem_post(philo->lock) != 0)
        return (EXIT_FAILURE);
    sleep_until(philo->last_eat_time + g_table->rules.eat_time);
    if (sem_post(g_table->forks) != 0 || sem_post(g_table->forks) != 0)
        return (EXIT_FAILURE);
    return (EXIT_SUCCESS);
}



uint8_t     philo_sleep(t_philo *const philo)
{
    sleep_until(philo_talk(philo, A_SLEEP, 1) + g_table->rules.sleep_time);
    philo_talk(philo, A_THINK, 1);
    return (EXIT_SUCCESS);
}
