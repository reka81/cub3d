/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars6.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:17:29 by zaheddac          #+#    #+#             */
/*   Updated: 2025/04/29 18:06:22 by mettalbi         ###   ########.fr       */
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
	int	j;
	int	total;

	g_visited = zyalloc(rows * sizeof(int *));
	g_visited[0] = zyalloc(rows * cols * sizeof(int));
	i = 1;
	while (i < rows)
	{
		g_visited[i] = g_visited[0] + (i * cols);
		i++;
	}
	i = 0;
	total = rows * cols;
	while (i < total)
	{
		g_visited[0][i] = 0;
		i++;
	}
}

void	free_visited(int rows)
{
	int	i;

	i = 0;
	while (i < rows)
		free (g_visited[i++]);
	free (g_visited);
}

void	flood_fill(char **map, int x, int y, t_coord *x_y)
{
	if (x < 0 || y < 0 || x >= x_y->rows || y >= (int)ft_strlen(map[x]))
		error_exit("Map is not closed (escaped bounds).");
	if (map[x][y] == ' ' || map[x][y] == '\0')
		error_exit("Map is not closed (hit space or invalid area).");
	if (map[x][y] == '1' || g_visited[x][y])
		return ;
	g_visited[x][y] = 1;
	flood_fill(map, x + 1, y, x_y);
	flood_fill(map, x - 1, y, x_y);
	flood_fill(map, x, y + 1, x_y);
	flood_fill(map, x, y - 1, x_y);
}
