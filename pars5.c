/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 13:13:05 by zaheddac          #+#    #+#             */
/*   Updated: 2025/04/26 10:53:24 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**store_map(char **strs)
{
	int		i;
	int		j;
	char	**map;
	int		e;

	i = 0;
	map = zyalloc(100 * sizeof(char *));
	e = 0;
	while (strs[i])
	{
		if ((strs[i][0] != 'N' && strs[i][1] != 'O' && strs[i][0] != 'S'
			&& strs[i][1] != 'O' && strs[i][0] != 'W' && strs[i][1] != 'E'
			&& strs[i][0] != 'E' && strs[i][1] != 'A') && (strs[i][0] != 'F'
			&& strs[i][0] != 'C' && strs [i][0] != 0)
			&& (if_only_spaces(strs[i]) == 1))
			while (strs[i])
				map[e++] = strs[i++];
		if (strs[i] == NULL)
			break ;
		i++;
	}
	map[e] = NULL;
	return (map);
}

char	**spaces_to_walls(char **map)
{
	int		i;
	int		j;
	char	**map_v2;
	int		ind;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == ' ')
			{
				map[i][j] = '1';
			}
			j++;
		}
		i++;
	}
	map_v2 = map;
	return (map_v2);
}

void	check_map2(char **strs, t_map_check *check_map)
{
	while (strs[check_map->len - 1][check_map->j])
	{
		if (strs[check_map->len - 1][check_map->j] != '1')
		{
			printf("the map is not closed\n");
			exit (1);
		}
		check_map->j++;
	}
	while (strs[check_map->i])
	{
		if (strs[check_map->i][0] != '1'
			|| strs[check_map->i][ft_strlen(strs[check_map->i]) - 1] != '1')
		{
			printf("the map is not closed\n");
			exit (1);
		}
		check_map->i++;
	}
}

void	check_map(char **strs)
{
	t_map_check	*check_map;

	check_map = zyalloc(sizeof(t_map_check));
	check_map->e = 0;
	check_map->i = 0;
	check_map->len = ft_strslen(strs);
	check_map->j = 0;
	while (strs[0][check_map->j])
	{
		if (strs[0][check_map->j] != '1')
		{
			printf("the map is not closed\n");
			exit (1);
		}
		check_map->j++;
	}
	check_map->j = 0;
}

void	only_6_char(char **strs)
{
	int	i;
	int	j;

	i = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] != '1' && strs[i][j] != '0' && strs[i][j] != 'N'
			&& strs[i][j] != 'S' && strs[i][j] != 'E' && strs[i][j] != 'W')
			{
				printf("invalid char in the map\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}
