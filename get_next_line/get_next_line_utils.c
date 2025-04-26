/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:45:43 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/26 10:53:24 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char *start, char *buff)
{
	char	*ptr;

	if (!buff)
		return (start);
	ptr = (char *)zyalloc(1 + ft_strlen(start) + ft_strlen(buff));
	if (!ptr)
		return (free(start), NULL);
	ptr = ft_complete(ptr, start, buff);
	free(start);
	return (ptr);
}

int	ft_strchr(char *s, int c)
{
	int		i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	if (s[i] == (char)c)
		return (1);
	return (0);
}

char	*ft_complete(char *dest, char *start, char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (start && start[i])
	{
		dest[i] = start[i];
		i++;
	}
	j = 0;
	while (buffer && buffer[j])
	{
		dest[i + j] = buffer[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}
