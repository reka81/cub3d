/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:09:19 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/29 15:05:39 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	its_a_wall(double x, double y, t_player *player)
{
	int	check_x;
	int	check_y;

	check_x = (int)x / 64;
	check_y = (int)y / 64;
	if (check_x < 0 || check_y < 0 || check_x >= player->longest_row
		|| check_y >= player->get_num_rows)
		return (0);
	if (check_y > (int)ft_strlen(player->staticarray[check_y]))
		check_y = check_y - 1;
	if (player->staticarray[check_y][check_x] == '1')
		return (1);
	else
		return (0);
}

void	player_init(t_player *player, char **staticArray, void *mlx, void *win)
{
	player->radius = 9;
	player->turn_direction = 0;
	player->walkdirection = 0;
	player->movespeed = 18.0;
	player->rotationspeed = (M_PI / 15);
	player->staticarray = staticArray;
	player->win = win;
	player->mlx = mlx;
}

int	its_a_wall3(double x, double y, t_player *player)
{
	t_wall_check	check;

	check.corner_x[0] = x - 10;
	check.corner_x[1] = x + 10;
	check.corner_y[0] = y - 10;
	check.corner_y[1] = y + 10;
	check.i = 0;
	while (check.i < 2)
	{
		check.j = 0;
		while (check.j < 2)
		{
			check.check_x = (int)(check.corner_x[check.i] / 64);
			check.check_y = (int)(check.corner_y[check.j] / 64);
			if (check.check_x < 0 || check.check_y < 0
				|| check.check_y >= player->get_num_rows
				|| check.check_x >= player->longest_row)
				return (1);
			if (player->staticarray[check.check_y][check.check_x] == '1')
				return (1);
			check.j++;
		}
		check.i++;
	}
	return (0);
}
