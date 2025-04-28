/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:28:37 by zaheddac          #+#    #+#             */
/*   Updated: 2025/04/28 15:08:08 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	openfd(char *str)
{
	int	fd;

	if (cheak_name(str) == 0)
	{
		fd = open(str, O_RDONLY);
		if (fd < 0)
		{
			printf("error : open failed\n");
			exit(1);
		}
	}
	else
	{
		printf("error : invalid map name\n");
		exit(1);
	}
	return (fd);
}

int	num_lines(int fd)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(fd);
	i++;
	if (line == NULL)
	{
		return (i);
	}
	while (line)
	{
		line = get_next_line(fd);
		i++;
	}
	return (i);
}

char	**store_2d_array(int fd, char *str)
{
	char	**strs;
	char	*line;
	int		i;

	i = 0;
	strs = zyalloc(sizeof(char *) * num_lines(fd) + 1);
	close(fd);
	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	if (line != NULL && line[0] != '\0')
		strs[i++] = line;
	while (line)
	{
		line = get_next_line(fd);
		if (line != NULL && line[0] != '\0')
			strs[i++] = line;
	}
	strs[i] = NULL;
	return (strs);
}

int	check_map_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '1' || str[i] == 'N' || str[i] == 'S'
			|| str[i] == '0' || str[i] == 'W' || str[i] == 'E'
			|| str[i] == ' ')
		{
			return (0);
		}
		i++;
	}
	return (1);
}

void	check_order(char **strs)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	len = ft_strslen(strs) - 1;
	while (len >= 0)
	{
		if (strs[len][0] != '\0')
		{
			if (check_map_line(strs[len]) == 1)
			{
				printf("error : order invalid");
				exit(1);
			}
			break ;
		}
		len--;
	}
}
