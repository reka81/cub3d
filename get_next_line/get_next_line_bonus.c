/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 21:16:56 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/26 10:53:24 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_line(char *str)
{
	char	*line;
	int		i;

	if (!str || !*str)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)zyalloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_new_str(char *str)
{
	char	*str2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	i += (str[i] == '\n');
	str2 = (char *)zyalloc(ft_strlen(str) + 1 - i);
	if (!str2)
		return (free(str), NULL);
	while (str[i + j])
	{
		str2[j] = str[i + j];
		j++;
	}
	str2[j] = '\0';
	free(str);
	return (str2);
}

char	*ft_filling(char *str, int fd)
{
	int		read_count;
	char	*tmp;

	tmp = (char *)zyalloc((size_t)BUFFER_SIZE + 1);
	if (!tmp)
		return (free(str), NULL);
	read_count = 1;
	while (ft_strchr(str, '\n') == 0 && read_count != 0)
	{
		read_count = read(fd, tmp, BUFFER_SIZE);
		if (read_count == -1)
		{
			free(tmp);
			free(str);
			return (NULL);
		}
		tmp[read_count] = '\0';
		str = ft_strjoin(str, tmp);
	}
	free(tmp);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[OPEN_MAX];	
	char		*tl;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	str[fd] = ft_filling(str[fd], fd);
	if (!str[fd])
	{
		free(str[fd]);
		return (NULL);
	}
	tl = ft_line(str[fd]);
	if (!tl)
		return (free(str[fd]), str[fd] = NULL, NULL);
	str[fd] = ft_new_str(str[fd]);
	return (tl);
}
