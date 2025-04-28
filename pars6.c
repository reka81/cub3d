/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:17:29 by zaheddac          #+#    #+#             */
/*   Updated: 2025/04/28 14:08:39 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

bool	g_visited[MAX_ROWS][MAX_COLS];

void	error_exit(const char *msg)
{
	fprintf(stderr, "Error: %s\n", msg);
	exit(EXIT_FAILURE);
}

void	flood_fill(char **map, int x, int y, int rows)
{
	if (x < 0 || y < 0 || x >= rows || y >= (int)ft_strlen(map[x]))
		error_exit("Map is not closed (escaped bounds).");
	if (map[x][y] == ' ' || map[x][y] == '\0')
		error_exit("Map is not closed (hit space or invalid area).");
	if (map[x][y] == '1' || g_visited[x][y])
		return ;
	g_visited[x][y] = true;
	flood_fill(map, x + 1, y, rows);
	flood_fill(map, x - 1, y, rows);
	flood_fill(map, x, y + 1, rows);
	flood_fill(map, x, y - 1, rows);
}

void	check_map_surrounded(char **map)
{
	int	start_x;
	int	start_y;
	int	rows;
	int	j;

	start_x = -1;
	start_y = -1;
	rows = 0;
	while (map[rows++])
	{
		j = -1;
		while (map[rows - 1][++j])
		{
			if (map[rows - 1][j] == 'N' || map[rows - 1][j] == 'E'
				|| map[rows - 1][j] == 'W' || map[rows - 1][j] == 'S')
			{
				start_x = rows - 1;
				start_y = j;
			}
		}
	}
	if (start_x == -1 || start_y == -1)
		error_exit("Player start 'N' not found in map.");
	memset(g_visited, 0, sizeof(g_visited));
	flood_fill(map, start_x, start_y, rows);
}
