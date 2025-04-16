/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:27:10 by zaheddac          #+#    #+#             */
/*   Updated: 2025/04/16 17:49:28 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int cheak_name(char *str)
{
	if (ft_strcmp(str + ft_strlen(str) - 4, ".cub") == 0)
		return (0);
	return (1);
}

int openfd(char *str)
{
	int fd;
	if (cheak_name(str) == 0)
	{
		fd = open(str, O_RDONLY);
		if (fd < 0)
		{
			printf("error\n");
			exit(1);
		}
	}
	else
	{
		printf("error\n");
		exit(1);
	}
	return (fd);
}

char **store_2d_array(int fd)
{
	char **strs;
	int i = 0;

	strs = malloc(100 * sizeof(char *));
	strs[i] = get_next_line(fd);
	while (strs[i] != NULL)
	{
		i++;
		strs[i] = get_next_line(fd);
	}
	return (strs);
}

int check_map_line(char *str)
{
	int i = 0;
	while (str[i]) 
	{
		if (str[i] != '1' && str[i] != 'N' && str[i] != 'S' && str[i] != '0' && str[i] != 'W' && str[i] != ' ')
		{
			return 1;
		}
		i++;
	}
    return 0;
}

void check_order(char **strs)
{
	int i = 0;
	int j = 0;

	while (strs[i])
	{
		if (strs[i + 1] == NULL)
		{
			if (check_map_line(strs[i]) == 1)
			{
				printf("errrrror");
				exit(1);
			}
		}
		i++;
	}
}

int check_texture_line(char *str)
{	
		if ((str[0] != 'N' && str[1] != 'O') && ( str[0] != 'S' && str[1] != 'O') && (str[0] != 'E' && str[1] != 'A'))
		{	
			return 1;
		}
	return 0;
}

int check_color_line(char *str)
{
	if (str[0] != 'C' && str[0] != 'F')
	{
		return 1;
	}
	return 0;
}

void check_invalid_inf(char **strs)
{
	int i = 0;
	while (strs[i])
	{
		if (check_map_line(strs[i]) == 1 && check_texture_line(strs[i]) == 1 && check_color_line(strs[i]) == 1)
		{
			printf("%serror : inv_line\n", strs[i]);
			exit(1);
		}
		i++;
	}
}

char **store_text(char **strs)
{
	int i;
	int j;
	char **textures;

	i = 0;
	j = 0;
	textures = malloc(sizeof(char *) * 1000);
	while (strs[i])
	{
		if (strs[i][0] == 'N' && strs[i][1] == 'O' || strs[i][0] == 'S' && strs[i][1] == 'O' || strs[i][0] == 'W' && strs[i][1] == 'E' || strs[i][0] == 'E' && strs[i][1] == 'A')
		{
			textures[j] = strs[i];
			j++;
		}
		i++;
	}
	textures[j] = NULL;
	return (textures);
}

char *get_path(char *str)
{
	int i;
	i = 0;
	char *path = NULL;
	while (str[i])
	{
		if (str[i] == '.' && str[i + 1] == '/')
		{
			path = str + i;
		}
		i++;
	}
	return (path);	
}

void cheak_path(char **strs)
{
	int i;
	int j;
	char *path;
	i = 0;
	while (strs[i])
	{
		path = get_path(strs[i]);
		if (path != NULL)
		{
			if (open(path, O_RDONLY) < 0)
			{
				printf("errorrr\n");
				exit(1);
			}
		}
		else
		{
			printf("error\n");
			exit(1);
		}
		i++;
	}
}

char **store_colors(char **strs)
{
	int i;
	int d;
	char **colors;

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

char *get_c_color(char **colors)
{
	int i;
	int j;
	char *c_color;
	int e;
	
	i = 0;
	e = 0;
	c_color = malloc(12);
	while (colors[i])
	{
		if (colors[i][0] == 'C')
		{
			j = 0;
			while (colors[i][j])
			{
				if ((colors[i][j] >= '0' && colors[i][j] <= '9') || colors[i][j] == ',')
				{
					c_color[e] = colors[i][j];
					e++;
				}
				j++;
			}
		}
		i++;
	}
	c_color[e] = '\0';
	return (c_color);
}

char **store_c_coloras2d(char *c_color)
{
	char **rgb_c_color;
	rgb_c_color = malloc(sizeof(char *) * 4);
	rgb_c_color[0] = malloc(4);
	rgb_c_color[1] = malloc(4);
	rgb_c_color[2] = malloc(4);
	int i = 0;
	int j = 0;
	int e = 0;
	while (c_color[i])
	{
		if (c_color[i] >= '0' && c_color[i] <= '9')
		{
			rgb_c_color[j][e] = c_color[i];
			e++;
		}
		else if (c_color[i] == ',')
		{
			rgb_c_color[j][e] = '\0';
			j++;
			e = 0;
		}
		i++;
	}
	if (c_color[i] == '\0')
	{
		rgb_c_color[j][e] = '\0';
		j++;
	}
	rgb_c_color[j] = NULL;
	return (rgb_c_color);
}

int rgb_to_int(char **rgb_c_color)
{
    int r = atoi(rgb_c_color[0]); 
    int g = atoi(rgb_c_color[1]);
    int b = atoi(rgb_c_color[2]);
	
	printf("%d--\n", r);
	printf("%d--\n", g);
	printf("%d--\n", b);
    return ( printf("Hexadecimal color code: #%06X\n", (r << 16) | (g << 8) | b));
}

int this_is_map(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] != '1' && str[i] != 'N' && str[i] != 'S' && str[i] != '0' && str[i] != 'W' && str[i] != 'W')
			return (1);
		i++;
	}
	return (0);
}

int if_only_spaces(char *str)
{
	int i = 0;

	while (str[i])
	{
		if (str[i] != ' ')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

char **store_map(char **strs)
{
	int i;
	int j;
	char **map;

	i = 0;
	map = malloc(100 * sizeof(char *));
	int e = 0;
	while (strs[i])
	{
		if ((strs[i][0] != 'N' && strs[i][1] != 'O' && strs[i][0] != 'S' && strs[i][1] != 'O' && strs[i][0] != 'W' && strs[i][1] != 'E' && strs[i][0] != 'E' && strs[i][1] != 'A') && (strs[i][0] != 'F' && strs[i][0] != 'C' && strs [i][0] != 0 ) && (if_only_spaces(strs[i]) == 1))
		{
			while (strs[i])
			{
				map[e] = strs[i];
				i++;
				e++;
			}
		}
		if (strs[i] == NULL)
			break ;
		i++;
	}
	map[e] = NULL;
	return (map);
}

char **spaces_to_walls(char **map)
{
	int i = 0;
	int j = 0;
	char **map_v2;
	int ind;
	i = 0;
	while (map[i])
	{
		j = 0;
		while(map[i][j])
		{
			if (map[i][j] == ' ')
			{
				if (map[i][j - 1] == '0')
				{
					map[i][j] = '0';
				}
				else if ((map[i][j + 1] == '0') && (j == 0))
				{
					map[i][j] = '0';
				}
				else if (map[i][j + 1] == ' ')
				{
					ind = j;
					while (map[i][ind] == ' ')
						ind++;
					if (map[i][ind] == '0')
						map[i][j] = '0';
					else 
						map[i][j] = '1';
				}
				else
					map[i][j] = '1';
			}
			j++;
		}
		i++;
	}
	map_v2 = map;
	return (map_v2);
}

int ft_strslen(char **strs)
{
	int i = 0;
	while (strs[i])
	{
		i++;
	}
	return (i);
}
void	check_map(char **strs)
{
	int	i;
	int	j;
	int len;
	int e = 0;
	int len1;
	int len2;

	i = 0;
	len = ft_strslen(strs);
	j = 0;
	while (strs[0][j])
	{
		if (strs[0][j] != '1')
		{
			printf("errorrr\n");
			exit (1);
		}
		j++;
	}
	j = 0;
	while (strs[len - 1][j])
	{
		if (strs[len - 1][j] != '1')
		{
			printf("errrror\n");
			exit (1);
		}
		j++;
	}
	while (strs[i])
	{
		if (strs[i][0] != '1' || strs[i][ft_strlen(strs[i]) - 1] != '1')
		{
			printf("error\n");
			exit (1);
		}
		i++;
	}
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
			if (strs[i][j] != '1' && strs[i][j] != '0' && strs[i][j] != 'N' && strs[i][j] != 'S'
				&& strs[i][j] != 'E' && strs[i][j] != 'W')
			{
				printf("error\n");
				exit(1);
			}
			j++;
		}
		i++;
	}
}

void check_new_line(char **strs)
{
	int i = 0;
	int j = 0;
	
	while (strs[i])
	{
		if (strs[i][0] == '\0')
		{
			printf("error");
			exit(1);
		}
		i++;
	}
}

t_strings *retrieving(int ac, char **av)
{
	int	fd;
	char **strs;
	char **colors;
	char *c_color;
	char **rgb_c_color;
	t_strings strings;
	
	printf("%d\n", ac);
	fd = openfd(av[1]);
	strs = store_2d_array(fd);
	check_order(strs);
	check_invalid_inf(strs);
	strings.texturs = store_text(strs);
	// cheak_path(strings.texturs);
	colors = store_colors(strs);
	c_color = get_c_color(colors);
	rgb_c_color = store_c_coloras2d(c_color);
	strings.map = store_map(strs);
	strings.map = spaces_to_walls(strings.map);
	only_6_char(strings.map);
	check_new_line(strings.map);
	check_map(strings.map);
	return &strings;
}
