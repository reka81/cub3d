/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:28:37 by zaheddac          #+#    #+#             */
/*   Updated: 2025/04/24 15:27:32 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	cheak_name(char *str)
{
	if (ft_strcmp(str + ft_strlen(str) - 4, ".cub") == 0)
		return (0);
	return (1);
}

int	openfd(char *str)
{
	int	fd;

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

char	**store_2d_array(int fd)
{
	char	**strs;
	int		i;

	i = 0;
	strs = malloc(100 * sizeof(char *));
	strs[i] = get_next_line(fd);
	while (strs[i] != NULL)
	{
		i++;
		strs[i] = get_next_line(fd);
	}
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
				printf("errrrror");
				exit(1);
			}
		}
		len--;
	}
}
