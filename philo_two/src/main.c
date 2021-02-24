#include "table.h"
#include <stdio.h>

// ./philo  <n_philo>  <time_die>  <time_eat>  <time_sleep>  [time_philos_eat]

int main(int ac, char **av)
{
    if (ac != 5 && ac != 6)
    {
        printf("Error: invalid input.\nUse : \
        ./philo_X <n_philo> <time_die> <time_eat> <time_sleep> [time_philos_eat]\n");
        return (EXIT_FAILURE);
    }
    t_table_rules rules = {
        .die_time = ft_atoi(av[2]),
        .eat_time = ft_atoi(av[3]),
        .sleep_time = ft_atoi(av[4]),
        .has_max_eat = 0
    };
    if (ac == 6)
    {
        rules.max_eat = ft_atoi(av[5]);
        rules.has_max_eat = 1;
    }
    else
        rules.max_eat = 0;
    printf ("Rules for %llu philosophers :\n- die_time: %d\n- eat_time: %d\n- sleep_time: %d\n- time_philo_eat: %d\n\n", ft_atoi(av[1]), rules.die_time, rules.eat_time, rules.sleep_time, rules.max_eat);
    return (init_table(rules, ft_atoi(av[1])));
}
