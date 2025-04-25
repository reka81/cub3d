/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:37:19 by zaheddac          #+#    #+#             */
/*   Updated: 2025/04/24 15:40:04 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r');
}

int	is_identifier_line(const char *line)
{
	while (*line == ' ')
	{
		if (strncmp(line, "NO", 2) == 0 && ft_isspace(line[2])
			|| strncmp(line, "SO", 2) == 0 && ft_isspace(line[2])
			|| strncmp(line, "WE", 2) == 0 && ft_isspace(line[2])
			|| strncmp(line, "EA", 2) == 0 && ft_isspace(line[2])
			|| line[0] == 'F' && ft_isspace(line[1])
			|| line[0] == 'C' && ft_isspace(line[1]))
		{
			return (0);
		}
		line++;
	}
	return (1);
}

int	is_empty_line(const char *line)
{
	while (*line)
	{
		if (!ft_isspace((unsigned char)*line))
		{
			return (1);
		}
		line++;
	}
	return (0);
}

int	maybe_map_line(const char *line)
{
	char	c;

	while (*line)
	{
		c = *line;
		if (c == '0' || c == '1' || c == 'N' || c == 'S'
			|| c == 'E' || c == 'W' || c == ' ')
		{
			return (0);
		}
		line++;
	}
	return (1);
}

void	check_invalid_inf(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (is_identifier_line(strs[i]) == 1 && is_empty_line(strs[i]) == 1
			&& maybe_map_line(strs[i]) == 1)
		{
			printf("error : inv_line\n");
			exit(1);
		}
		i++;
	}
}
