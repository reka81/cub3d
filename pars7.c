/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:57:33 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/25 11:59:32 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	struct_fill(t_store_clrs **storing)
{
	*storing = malloc(sizeof(t_store_clrs));
	(*storing)->rgb_f_color = malloc(sizeof(char *) * 4);
	(*storing)->rgb_f_color[0] = malloc(4);
	(*storing)->rgb_f_color[1] = malloc(4);
	(*storing)->rgb_f_color[2] = malloc(4);
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
