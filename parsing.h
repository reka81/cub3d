/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:32:31 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/29 18:06:30 by mettalbi         ###   ########.fr       */
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

size_t	ft_strlen(const char *str);
int		ft_strcmp(char *s1, char *s2);
char	**ft_split(char const *s, char c);

typedef struct s_strings
{
	char	**texturs;
	char	*no_texture;
	char	*so_texture;
	char	*ea_texture;
	char	*we_texture;
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

typedef struct coord
{
	int	rows;
	int	cols;
}	t_coord;

int		openfd(char *str);
char	**store_2d_array(int fd, char *str);
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
void	cheak_path(char **strs);
char	*store_texture(char **textures, char *type);
void	*zyalloc(long long size);
void	allocating(t_strings **strings, t_pars **parsing, char **av);
char	**store_text(char **strs);
int		rgb_to_int(char **rgb_c_color);
void	check_new_line(char **strs);
int		count_duplicate(char **strs, char *type);
void	check_duplicate_textures(char **strs);
void	check_duplicate_colors(char **strs);
int		count_num_players(char **strs);
void	check_duplicate_player(char **strs);
void	check_correct_num_args(int ac);
int		cheak_name(char *str);
int		is_identifier_line(const char *line);
int		is_empty_line(const char *line);
int		virify_map_line(char *line);
int		maybe_map_line(char *line);
void	err_check2(int e);
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int value, size_t len);
void	allocate_visited(int rows, int cols);
void	error_exit(const char *msg);
void	flood_fill(char **map, int x, int y, t_coord *x_y);
void	free_visited(int rows);
#endif