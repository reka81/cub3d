/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_part3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:02:48 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/26 11:32:12 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_num_rows(char **array)
{
	int	num_rows;

	num_rows = 0;
	while (array[num_rows] != NULL)
	{
		num_rows++;
	}
	return (num_rows);
}

int	get_longest_row(char **map)
{
	int	i;
	int	max_len;
	int	len;

	i = 0;
	max_len = 0;
	while (map[i] != NULL)
	{
		len = ft_strlen(map[i]);
		if (len > max_len)
			max_len = len;
		i++;
	}
	return (max_len);
}

char	**pad_map(char **map, int num_rows, int longest_row, char pad_char)
{
	int		i;
	char	**padded_map;
	int		len;
	int		j;

	padded_map = zyalloc(sizeof(char *) * (num_rows + 1));
	if (!padded_map)
		return (NULL);
	i = 0;
	while (i < num_rows)
	{
		len = ft_strlen(map[i]);
		padded_map[i] = zyalloc(longest_row + 1);
		if (!padded_map[i])
			return (NULL);
		ft_strcpy(padded_map[i], map[i]);
		j = len;
		while (j < longest_row)
		{
			padded_map[i][j++] = pad_char;
		}
		padded_map[i++][longest_row] = '\0';
	}
	padded_map[num_rows] = NULL;
	return (padded_map);
}

void	setting_angle(char **map, t_player *player, int i, int j)
{
	player->x = 64 * j + 0.5f;
	player->y = 64 * i +0.5f;
	if (map[i][j] == 'N')
		player->rotationangle = M_PI / 2;
	if (map[i][j] == 'S')
		player->rotationangle = 3 * M_PI / 2;
	if (map[i][j] == 'W')
		player->rotationangle = M_PI;
	if (map[i][j] == 'E')
		player->rotationangle = 2 * M_PI;
}

void	locate_player(t_player *player, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'W' || map[i][j] == 'E')
			{
				setting_angle(map, player, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}
