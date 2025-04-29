/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:57:33 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/29 15:26:29 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	struct_fill(t_store_clrs **storing)
{
	*storing = zyalloc(sizeof(t_store_clrs));
	(*storing)->rgb_f_color = zyalloc(sizeof(char *) * 4);
	(*storing)->rgb_f_color[0] = zyalloc(4);
	(*storing)->rgb_f_color[1] = zyalloc(4);
	(*storing)->rgb_f_color[2] = zyalloc(4);
	(*storing)->i = 0;
	(*storing)->j = 0;
	(*storing)->e = 0;
}

int	if_only_spaces(char *str)
{
	int	i;

	i = 0;
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
