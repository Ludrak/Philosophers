/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 11:41:56 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 08:29:56 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "table.h"
#include <stdio.h>

static int	check_rules(t_table_rules rules, char **av, uint16_t n_philo)
{
	if (!ft_isnum(av[1]) || !ft_isnum(av[2]) || !ft_isnum(av[3])
		|| !ft_isnum(av[4]) || (rules.has_max_eat && !ft_isnum(av[5])))
		return (printf ("Error: invalid parameters are non numeric.\n")
			* 0 + 1);
	if (rules.die_time > INT32_MAX || rules.eat_time > INT32_MAX
		|| rules.sleep_time > INT32_MAX
		|| (rules.has_max_eat && rules.max_eat > INT32_MAX))
		return (printf ("Error: invalid parameters goes above MAX_INT.\n")
			* 0 + 1);
	if (rules.die_time < 1 || rules.eat_time < 1 || rules.sleep_time < 1
		|| (rules.has_max_eat && rules.max_eat < 1))
		return (printf ("Error: null or negatives values are not allowed.\n")
			* 0 + 1);
	if (n_philo <= 1)
		return (printf ("Error: at least 2 philosophers are required.\n")
			* 0 + 1);
	else if (n_philo > MAX_THREADS)
		return (printf("Error: too many philosophers.\n") * 0 + 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_table_rules	rules;

	if (ac != 5 && ac != 6)
		return (printf ("Error: invalid parameters\n") + EXIT_FAILURE);
	rules.die_time = ft_atoi(av[2]);
	rules.eat_time = ft_atoi(av[3]);
	rules.sleep_time = ft_atoi(av[4]);
	rules.has_max_eat = 0;
	if (ac == 6)
	{
		rules.max_eat = ft_atoi(av[5]);
		rules.has_max_eat = 1;
	}
	else
		rules.max_eat = 0;
	return (check_rules(rules, av, ft_atoi(av[1]))
		|| init_table(rules, ft_atoi(av[1])));
}
