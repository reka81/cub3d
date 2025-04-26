/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 21:15:44 by zaheddac          #+#    #+#             */
/*   Updated: 2025/04/26 10:53:24 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_to_str(int fd, char *str)
{
	char	*buffer;
	int		n_byte;

	buffer = zyalloc(((size_t)BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(str), str = NULL, NULL);
	n_byte = 1;
	while (!ft_strchr(str, '\n') && n_byte != 0)
	{
		n_byte = read(fd, buffer, BUFFER_SIZE);
		if (n_byte == -1)
			return (free(str), free(buffer), NULL);
		buffer[n_byte] = '\0';
		str = ft_strjoin(str, buffer);
		if (!str)
			break ;
	}
	free (buffer);
	return (str);
}

char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)zyalloc((i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	return (line[i] = '\0', line);
}

char	*ft_new_str(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
		return (free(str), NULL);
	new_str = zyalloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!new_str)
		return (free(str), str = NULL, NULL);
	i++;
	j = 0;
	while (str[i])
	{
		new_str[j] = str[i];
		i++;
		j++;
	}
	new_str[j] = '\0';
	return (free(str), str = NULL, new_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	if (!str)
		str = ft_strdup("");
	if (!str)
		return (NULL);
	str = ft_read_to_str(fd, str);
	if (!str)
		return (NULL);
	line = ft_get_line(str);
	if (!line)
		return (free(str), str = NULL, NULL);
	str = ft_new_str(str);
	return (line);
}
