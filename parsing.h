#ifndef PARSING_H
#define PARSING_H

# include "./get_next_line/get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

size_t	ft_strlen(const char *str);
int ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);

typedef struct s_strings
{
	char **texturs;
	int	C_color;
	int F_color;
	char **map;
} t_strings;

#endif