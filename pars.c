/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:10 by zaheddac          #+#    #+#             */
/*   Updated: 2025/04/29 15:39:57 by mettalbi         ###   ########.fr       */
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

void	err_code(int ind)
{
	if (ind != 2)
	{
		printf("error : invalid color\n");
		exit(1);
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
		if ((color[i] != ',' && color[i] < '0') || color[i] > '9')
		{
			printf("error : invalid color\n");
			exit(1);
		}
		else if (color[i] == ',')
		{
			ind++;
			if ((color[i + 1] < '0' || color[i + 1] > '9')
				|| (color[i - 1] < '0' || color[i - 1] > '9'))
			{
				printf("error : invalid color\n");
				exit(1);
			}
		}
		i++;
	}
	err_code(ind);
}

t_strings	*retrieving(int ac, char **av)
{
	t_pars		*parsing;
	char		*f_color;
	char		**rgb_c_color;
	char		**rgb_f_color;
	t_strings	*strings;

	check_correct_num_args(ac);
	allocating(&strings, &parsing, av);
	parsing->c_color = get_c_color(parsing->colors);
	pars_color(parsing->c_color);
	rgb_c_color = store_c_coloras2d(parsing->c_color);
	check_range(rgb_c_color);
	strings->c_color = rgb_to_int(rgb_c_color);
	strings->map = store_map(parsing->strs);
	check_new_line(strings->map);
	check_duplicate_player(strings->map);
	f_color = get_f_color(parsing->colors);
	pars_color(f_color);
	rgb_f_color = store_f_coloras2d(f_color);
	check_range(rgb_f_color);
	strings->f_color = rgb_to_int(rgb_f_color);
	check_map_surrounded(strings->map);
	strings->map = spaces_to_walls(strings->map);
	only_6_char(strings->map);
	return (strings);
}
