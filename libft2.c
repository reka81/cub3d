/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:27:47 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/26 10:53:24 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	char	**fill_words(char **str, const char *s, char c, int count)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[j] && i < count)
	{
		len = 0;
		while (s[j] == c && s[j])
			j++;
		while (s[j + len] != c && s[j + len])
			len++;
		if (len != 0)
		{
			str[i] = zyalloc((len + 1) * sizeof(char));
			if (!str[i])
				return (ft_free(str, i));
			ft_strlcpy(str[i], (s + j), len + 1);
			j = j + len;
			i++;
		}
	}
	str[i] = NULL;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	char	**str;

	if (!s)
	{
		return (NULL);
	}
	str = zyalloc((count_strings(s, c) + 1) * sizeof(char *));
	if (!str)
		return (NULL);
	return (fill_words(str, s, c, count_strings(s, c)));
}
