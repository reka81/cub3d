/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 11:47:09 by zaheddac          #+#    #+#             */
/*   Updated: 2025/04/29 15:48:01 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*get_path(char *str)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
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

void	cheak_path(char **strs)
{
	int		i;
	char	*path;

	i = 0;
	while (strs[i])
	{
		path = get_path(strs[i]);
		if (path != NULL)
		{
			if (open(path, O_RDONLY) < 0)
			{
				printf("error : invalid path\n");
				exit(1);
			}
		}
		else
		{
			printf("error : invalid path\n");
			exit(1);
		}
		i++;
	}
}

char	*store_texture(char **textures, char *type)
{
	int		i;
	char	*texture;

	i = 0;
	while (textures[i])
	{
		if (textures[i][0] == type[0] && textures[i][1] == type[1])
		{
			texture = get_path(textures[i]);
		}
		i++;
	}
	return (texture);
}

void	err_check2(int e)
{
	if (e > 3)
	{
		printf("error : colore is bigger than range\n");
		exit(1);
	}
}
