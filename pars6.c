/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:17:29 by zaheddac          #+#    #+#             */
/*   Updated: 2025/04/29 16:54:32 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	**g_visited;

void	error_exit(const char *msg)
{
	fprintf(stderr, "Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

void	allocate_visited(int rows, int cols)
{
	int	i;

	i = 0;
	g_visited = malloc(rows * sizeof(int *));
	if (!g_visited)
		error_exit("Memory allocation failed.");
	while (i < rows)
	{
		g_visited[i] = calloc(cols, sizeof(int));
		if (!g_visited[i])
			error_exit("Memory allocation failed.");
		i++;
	}
}

void	free_visited(int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(g_visited[i]);
		i++;
	}
	free(g_visited);
}

void	flood_fill(char **map, int x, int y, int rows, int cols)
{
	if (x < 0 || y < 0 || x >= rows || y >= ft_strlen(map[x]))
		error_exit("Map is not closed (escaped bounds).");
	if (map[x][y] == ' ' || map[x][y] == '\0')
		error_exit("Map is not closed (hit space or invalid area).");
	if (map[x][y] == '1' || g_visited[x][y])
		return ;
	g_visited[x][y] = 1;
	flood_fill(map, x + 1, y, rows, cols);
	flood_fill(map, x - 1, y, rows, cols);
	flood_fill(map, x, y + 1, rows, cols);
	flood_fill(map, x, y - 1, rows, cols);
}

void	check_map_surrounded(char **map)
{
	int	start_x;
	int	start_y;
	int	rows;
	int	cols;
	int	i;
	int	j;
	int	len;

	i = 0;
	rows = 0;
	cols = 0;
	start_x = -1;
	start_y = -1;
	while (map[rows])
		rows++;
	i = 0;
	while (i < rows)
	{
		len = ft_strlen(map[i]);
		if (len > cols)
			cols = len;
		i++;
	}
	allocate_visited(rows, cols);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'E'
				|| map[i][j] == 'W' || map[i][j] == 'S')
			{
				start_x = i;
				start_y = j;
			}
			j++;
		}
		i++;
	}
	if (start_x == -1 || start_y == -1)
		error_exit("Player start 'N' not found in map.");
	flood_fill(map, start_x, start_y, rows, cols);
	printf("Map is valid and fully enclosed by walls.\n");
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
