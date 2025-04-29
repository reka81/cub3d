/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_6_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:18:27 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/29 17:51:05 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	get_map_rows(char **map)
{
	int	rows;

	rows = 0;
	while (map[rows])
	{
		rows++;
	}
	return (rows);
}

int	get_max_cols(char **map, int rows)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (i < rows)
	{
		len = ft_strlen(map[i]);
		if (len > max)
		{
			max = len;
		}
		i++;
	}
	return (max);
}

void	find_player_start(char **map, int rows, int *x, int *y)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'W' || map[i][j] == 'S')
			{
				*x = i;
				*y = j;
			}
			j++;
		}
		i++;
	}
}

void	check_map_surrounded(char **map)
{
	int		rows;
	int		cols;
	int		start_x;
	int		start_y;
	t_coord	*x_y;

	x_y = zyalloc(sizeof(x_y));
	start_x = -1;
	start_y = -1;
	rows = get_map_rows(map);
	cols = get_max_cols(map, rows);
	allocate_visited(rows, cols);
	find_player_start(map, rows, &start_x, &start_y);
	if (start_x == -1 || start_y == -1)
	{
		error_exit("Player start not found.");
	}
	x_y->rows = rows;
	x_y->cols = cols;
	flood_fill(map, start_x, start_x, x_y);
	free_visited(rows);
}

void	allocating(t_strings **strings, t_pars **parsing, char **av)
{
	*strings = zyalloc(sizeof(t_strings));
	*parsing = zyalloc(sizeof(t_pars));
	(*parsing)->fd = openfd(av[1]);
	(*parsing)->strs = store_2d_array((*parsing)->fd, av[1]);
	check_invalid_inf((*parsing)->strs);
	check_order((*parsing)->strs);
	(*strings)->texturs = store_text((*parsing)->strs);
	check_duplicate_textures((*strings)->texturs);
	cheak_path((*strings)->texturs);
	(*strings)->no_texture = store_texture((*strings)->texturs, "NO");
	(*strings)->so_texture = store_texture((*strings)->texturs, "SO");
	(*strings)->ea_texture = store_texture((*strings)->texturs, "EA");
	(*strings)->we_texture = store_texture((*strings)->texturs, "WE");
	(*parsing)->colors = store_colors((*parsing)->strs);
}
