
#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>

/*
**  Conversion
*/
uint64_t    ft_atoi(char *s);
char        *ft_itoa(uint64_t n);

/*
**  Strings
*/
size_t      ft_strlen(char *s);
char        *ft_strjoin(char *s1, char *s2);

#endif