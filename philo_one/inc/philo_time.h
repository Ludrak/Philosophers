/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_time.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 08:43:51 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 08:44:13 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TIME_H
# define PHILO_TIME_H

# include <sys/time.h>
# include <unistd.h>
# include <stdlib.h>

uint64_t	get_time(void);
uint64_t	get_time_since(const uint64_t time);
void		sleep_until(const uint64_t time);

#endif