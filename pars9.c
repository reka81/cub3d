/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars9.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:45:58 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/27 22:46:43 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	count_duplicate(char **strs, char *type)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (strs[i])
	{
		if (type[1] != '\0')
		{
			if (strs[i][0] == type[0] && strs[i][1] == type[1])
				count++;
		}
		else
		{
			if (strs[i][0] == type[0])
				count++;
		}
		i++;
	}
	return (count);
}

void	check_duplicate_textures(char **strs)
{
	if (count_duplicate(strs, "NO") > 1)
	{
		printf("error ; duplicate");
		exit(1);
	}
	else if (count_duplicate(strs, "SO") > 1)
	{
		printf("error ; duplicate");
		exit(1);
	}
	else if (count_duplicate(strs, "EA") > 1)
	{
		printf("error ; duplicate");
		exit(1);
	}
	else if (count_duplicate(strs, "WE") > 1)
	{
		printf("error ; duplicate");
		exit(1);
	}
}

void	check_duplicate_colors(char **strs)
{
	if (count_duplicate(strs, "F") > 1)
	{
		printf("error ; duplicate");
		exit(1);
	}
	else if (count_duplicate(strs, "C") > 1)
	{
		printf("error ; duplicate");
		exit(1);
	}
}

int	count_num_players(char **strs)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == 'N' || strs[i][j] == 'S'
				|| strs[i][j] == 'E' || strs[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	return (count);
}

void	check_duplicate_player(char **strs)
{
	if (count_num_players(strs) > 1)
	{
		printf("error ; duplicate");
		exit(1);
	}
}
