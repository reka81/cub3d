/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 10:27:47 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/29 15:55:32 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "cub3d.h"

int	cheak_name(char *str)
{
	if (ft_strcmp(str + ft_strlen(str) - 4, ".cub") == 0)
		return (0);
	return (1);
}

int	exit_window(t_player *player)
{
	mlx_destroy_window(player->mlx, player->win);
	exit(0);
}

void	check_correct_num_args(int ac)
{
	if (ac != 2)
	{
		printf("error: incorrect num args\n");
		exit(1);
	}
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

int	ft_atoi(const char *str)
{
	int			sign;
	long long	result;
	long long	tmp;

	sign = 1;
	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		tmp = result * 10 + (*str++ - '0');
		if (tmp < result && sign == 1)
			return (-1);
		if (tmp < result && sign == -1)
			return (0);
		result = tmp;
	}
	return (result * sign);
}
