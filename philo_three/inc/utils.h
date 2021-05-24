/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 09:36:11 by lrobino           #+#    #+#             */
/*   Updated: 2021/05/24 09:36:51 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>
# include <stdlib.h>

/*
**  Conversion
*/
uint64_t	ft_atoui(const char *s);
char		*ft_uitoa(uint64_t n);

/*
**  Strings
*/
size_t		ft_strlen(const char *const s);
char		*ft_strjoin(const char *s1, char *s2);
uint8_t		ft_isnum(char *s);

void		*nmalloc(void **ptr, size_t size, size_t block);

#endif
