/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 08:45:53 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 08:45:55 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>

uint64_t	ft_atoi(char *s);

uint8_t		ft_isnum(char *s);

void		*nmalloc(void **ptr, size_t size, size_t block);

#endif