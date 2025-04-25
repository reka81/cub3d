/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:20:32 by zaheddac          #+#    #+#             */
/*   Updated: 2025/04/25 11:02:24 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	**store_colors(char **strs)
{
	int		i;
	int		d;
	char	**colors;

	i = 0;
	d = 0;
	colors = malloc(sizeof(char *) * 100);
	while (strs[i])
	{
		if (strs[i][0] == 'F' || strs[i][0] == 'C')
		{
			colors[d] = strs[i];
			d++;
		}
		i++;
	}
	colors[d] = NULL;
	return (colors);
}

char	*get_c_color(char **colors)
{
	int		i;
	int		e;
	int		j;
	char	*c_color;

	i = 0;
	e = 0;
	c_color = malloc(12);
	while (colors[i])
	{
		if (colors[i][0] == 'C')
		{
			j = 0;
			while (colors[i][j])
				if ((colors[i][j] >= '0' && colors[i][j] <= '9')
					|| colors[i][j] == ',')
					c_color[e++] = colors[i][j++];
			else
				j++;
		}
		i++;
	}
	c_color[e] = '\0';
	return (c_color);
}

char	*get_f_color(char **colors)
{
	int		i;
	int		j;
	char	*c_color;
	int		e;

	i = 0;
	e = 0;
	c_color = malloc(12);
	while (colors[i])
	{
		if (colors[i][0] == 'F')
		{
			j = 0;
			while (colors[i][j])
				if ((colors[i][j] >= '0' && colors[i][j] <= '9')
					|| colors[i][j] == ',')
					c_color[e++] = colors[i][j++];
			else
				j++;
		}
		i++;
	}
	c_color[e] = '\0';
	return (c_color);
}

char	**store_c_coloras2d(char *c_color)
{
	t_store_clrs	*storing;

	struct_fill(&storing);
	while (c_color[storing->i])
	{
		if (c_color[storing->i] >= '0' && c_color[storing->i] <= '9')
		{
			storing->rgb_f_color[storing->j][storing->e] = c_color[storing->i];
			storing->e++;
		}
		else if (c_color[storing->i] == ',')
		{
			storing->rgb_f_color[storing->j][storing->e] = '\0';
			storing->j++;
			storing->e = 0;
		}
		storing->i++;
	}
	if (c_color[storing->i] == '\0')
	{
		storing->rgb_f_color[storing->j][storing->e] = '\0';
		storing->j++;
	}
	storing->rgb_f_color[storing->j] = NULL;
	return (storing->rgb_f_color);
}

char	**store_f_coloras2d(char *f_color)
{
	t_store_clrs	*storing;

	struct_fill(&storing);
	while (f_color[storing->i])
	{
		if (f_color[storing->i] >= '0' && f_color[storing->i] <= '9')
		{
			storing->rgb_f_color[storing->j][storing->e] = f_color[storing->i];
			storing->e++;
		}
		else if (f_color[storing->i] == ',')
		{
			storing->rgb_f_color[storing->j][storing->e] = '\0';
			storing->j++;
			storing->e = 0;
		}
		storing->i++;
	}
	if (f_color[storing->i] == '\0')
	{
		storing->rgb_f_color[storing->j][storing->e] = '\0';
		storing->j++;
	}
	storing->rgb_f_color[storing->j] = NULL;
	return (storing->rgb_f_color);
}
