/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:09:19 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/23 16:38:59 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	its_a_wall(double x, double y, t_player *player)
{
	int	check_x;
	int	check_y;

	check_x = x / 64;
	check_y = y / 64;
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
	player->movespeed = 10.0;
	player->rotationspeed = (M_PI / 25);
	player->staticarray = staticArray;
	player->win = win;
	player->mlx = mlx;
}
