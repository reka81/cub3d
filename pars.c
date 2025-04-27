/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:10 by zaheddac          #+#    #+#             */
/*   Updated: 2025/04/27 22:48:16 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_num(char *c_color)
{
	int	color;

	color = atoi(c_color);
	if (color < 0 || color > 255)
		return (1);
	return (0);
}

void	check_range(char **rgb_c_color)
{
	int	i;

	i = 0;
	while (rgb_c_color[i])
	{
		if (check_num(rgb_c_color[i]) == 1)
		{
			printf("error : colore is bigger than range");
			exit(1);
		}
		i++;
	}
}

void	pars_color(char *color)
{
	int	i;
	int	ind;

	ind = 0;
	i = 0;
	while (color[i] != '\0')
	{
		if (color[i] != ',' && color[i] < '0' || color[i] > '9')
		{
			printf("error\n");
			exit(1);
		}
		else if (color[i] == ',')
		{
			ind++;
			if ((color[i + 1] < '0' || color[i + 1] > '9')
				|| (color[i - 1] < '0' || color[i - 1] > '9'))
			{
				printf("error\n");
				exit(1);
			}
		}
		i++;
	}
	if (ind != 2)
	{
		printf("error\n");
		exit(1);
	}
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
	check_duplicate_textures(strings->texturs);
	cheak_path(strings->texturs);
	strings->no_texture = store_texture(strings->texturs, "NO");
	strings->so_texture = store_texture(strings->texturs, "SO");
	strings->ea_texture = store_texture(strings->texturs, "EA");
	strings->we_texture = store_texture(strings->texturs, "WE");
	parsing->colors = store_colors(parsing->strs);
	check_duplicate_colors(parsing->colors);
	parsing->c_color = get_c_color(parsing->colors);
	pars_color(parsing->c_color);
	rgb_c_color = store_c_coloras2d(parsing->c_color);
	check_range(rgb_c_color);
	strings->c_color = rgb_to_int(rgb_c_color);
	strings->map = store_map(parsing->strs);
	check_duplicate_player(strings->map);
	f_color = get_f_color(parsing->colors);
	pars_color(f_color);
	rgb_f_color = store_f_coloras2d(f_color);
	strings->f_color = rgb_to_int(rgb_f_color);
	check_map_surrounded(strings->map);
	strings->map = spaces_to_walls(strings->map);
	only_6_char(strings->map);
	check_new_line(strings->map);
	return (strings);
}
