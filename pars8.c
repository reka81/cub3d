/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:48:36 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/29 15:11:53 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	err_check(int err)
{
	if (err < 4)
	{
		printf("error: texture not found\n");
		exit(1);
	}
}

char	**store_text(char **strs)
{
	int		i;
	int		j;
	char	**textures;
	int		err;

	i = 0;
	j = 0;
	err = 0;
	textures = (char **)zyalloc(sizeof(char *) * ft_strslen(strs));
	while (strs[i])
	{
		if ((strs[i][0] == 'N' && strs[i][1] == 'O') || (strs[i][0] == 'S'
			&& strs[i][1] == 'O') || (strs[i][0] == 'W' && strs[i][1] == 'E')
				|| (strs[i][0] == 'E' && strs[i][1] == 'A'))
		{
			textures[j] = strs[i];
			j++;
			err++;
		}
		i++;
	}
	err_check(err);
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

int	new_line_map(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (strs[i][0] == '\0')
		{
			while (strs[i])
			{
				if (strs[i][0] != '\0' && if_only_spaces(strs[i]) == 1)
					return (1);
				i++;
			}
			if (strs[i] == NULL)
				break ;
		}
		i++;
	}
	return (0);
}

void	check_new_line(char **strs)
{
	if (new_line_map(strs) == 1)
	{
		printf("new line in the map");
		exit(1);
	}
}
