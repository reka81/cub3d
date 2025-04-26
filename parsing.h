/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:32:31 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/26 10:54:41 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

# define MAX_ROWS 100
# define MAX_COLS 100

size_t	ft_strlen(const char *str);
int		ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);

typedef struct s_strings
{
	char	**texturs;
	int		c_color;
	int		f_color;
	char	**map;
}	t_strings;

typedef struct s_pars
{
	int		fd;
	char	**strs;
	char	**colors;
	char	*c_color;	
}	t_pars;

typedef struct s_map_check
{
	int	i;
	int	j;
	int	len;
	int	e;
	int	len1;
	int	len2;
}	t_map_check;

typedef struct s_store_clrs
{
	char	**rgb_f_color;
	int		i;
	int		j;
	int		e;	
}	t_store_clrs;

int		openfd(char *str);
char	**store_2d_array(int fd);
void	check_invalid_inf(char **strs);
void	check_order(char **strs);
char	**store_colors(char **strs);
char	*get_c_color(char **colors);
char	**store_c_coloras2d(char *c_color);
char	**store_map(char **strs);
char	*get_f_color(char **colors);
char	**store_f_coloras2d(char *f_color);
void	check_map_surrounded(char **map);
char	**spaces_to_walls(char **map);
void	only_6_char(char **strs);
int		ft_strslen(char **strs);
void	struct_fill(t_store_clrs **storing);
int		if_only_spaces(char *str);
void	*zyalloc(long long size);
#endif