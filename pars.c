/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:10 by zaheddac          #+#    #+#             */
/*   Updated: 2025/04/26 10:53:24 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**store_text(char **strs)
{
	int		i;
	int		j;
	char	**textures;

	i = 0;
	j = 0;
	textures = (char **)zyalloc(sizeof(char *) * 1000);
	while (strs[i])
	{
		if (strs[i][0] == 'N' && strs[i][1] == 'O' || strs[i][0] == 'S'
			&& strs[i][1] == 'O' || strs[i][0] == 'W' && strs[i][1] == 'E'
				|| strs[i][0] == 'E' && strs[i][1] == 'A')
		{
			textures[j] = strs[i];
			j++;
		}
		i++;
	}
	textures[j] = NULL;
	return (textures);
}

int	rgb_to_int(char **rgb_c_color)
{
	int	r;
	int	g;
	int	b;

	g = atoi(rgb_c_color[1]);
	r = atoi(rgb_c_color[0]);
	b = atoi(rgb_c_color[2]);
	return ((r << 16) | (g << 8) | b);
}

void	check_new_line(char **strs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strs[i])
	{
		if (strs[i][0] == '\0')
		{
			printf("new line in the map");
			exit(1);
		}
		i++;
	}
}

void	allocating(t_strings **strings, t_pars **parsing, char **av)
{
	*strings = zyalloc(sizeof(t_strings));
	*parsing = zyalloc(sizeof(t_pars));
	(*parsing)->fd = openfd(av[1]);
	(*parsing)->strs = store_2d_array((*parsing)->fd);
}

t_strings	*retrieving(int ac, char **av)
{
	t_pars		*parsing;
	char		*f_color;
	char		**rgb_c_color;
	char		**rgb_f_color;
	t_strings	*strings;

	allocating(&strings, &parsing, av);
	check_invalid_inf(parsing->strs);
	check_order(parsing->strs);
	strings->texturs = store_text(parsing->strs);
	// cheak_path(strings.texturs);
	parsing->colors = store_colors(parsing->strs);
	parsing->c_color = get_c_color(parsing->colors);
	rgb_c_color = store_c_coloras2d(parsing->c_color);
	strings->c_color = rgb_to_int(rgb_c_color);
	strings->map = store_map(parsing->strs);
	f_color = get_f_color(parsing->colors);
	rgb_f_color = store_f_coloras2d(f_color);
	strings->f_color = rgb_to_int(rgb_f_color);
	check_map_surrounded(strings->map);
	strings->map = spaces_to_walls(strings->map);
	only_6_char(strings->map);
	check_new_line(strings->map);
	return (strings);
}
