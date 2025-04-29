/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 17:42:50 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/29 13:25:32 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	distance_between(double player_x, double player_y,
		double wall_hitx, double wall_hity)
{
	return (sqrt((player_x - wall_hitx) * (player_x - wall_hitx)
			+ (player_y - wall_hity) * (player_y - wall_hity)));
}

void	check_horizontal_inter2(t_ray *rays, int i, t_player *player)
{
	rays[i].y_step = 0;
	rays[i].xstep = 0;
	rays[i].next_touch_y = 0;
	rays[i].next_touch_x = 0;
	rays[i].x_interecept = 0;
	rays[i].y_interecept = 0;
	rays[i].wall_found = 0;
	rays[i].y_interecept = floor(player->y / 64) * 64;
}

void	check_horizontal_inter3(t_ray *rays, t_player *player, int i)
{
	if (rays[i].downward_ray == 1)
		rays[i].y_interecept += 64;
	rays[i].x_interecept = player->x + (player->y - rays[i].y_interecept)
		/ tan(rays[i].ray_angle);
	rays[i].y_step = 64;
	if (rays[i].upward_ray == 1)
		rays[i].y_step *= -1;
	rays[i].xstep = 64 / tan(rays[i].ray_angle);
	if (rays[i].left_ray == 1 && rays[i].xstep > 0)
		rays[i].xstep *= -1;
	if (rays[i].right_ray == 1 && rays[i].xstep < 0)
		rays[i].xstep *= -1;
}

void	check_horizontal_inter(t_player *player, t_ray *rays, int i)
{
	double	y_check;

	check_horizontal_inter2(rays, i, player);
	check_horizontal_inter3(rays, player, i);
	rays[i].next_touch_x = rays[i].x_interecept;
	rays[i].next_touch_y = rays[i].y_interecept;
	while (rays[i].next_touch_x >= 0
		&& rays[i].next_touch_x <= 64 * player->longest_row
		&& rays[i].next_touch_y >= 0
		&& rays[i].next_touch_y <= 64 * player->get_num_rows)
	{
		y_check = rays[i].next_touch_y;
		if (rays[i].upward_ray == 1)
			y_check--;
		if (its_a_wall(rays[i].next_touch_x, y_check, player)
			|| rays[i].next_touch_y == 64)
		{
			rays[i].wall_found = 1;
			rays[i].wallhitx = rays[i].next_touch_x;
			rays[i].wallhity = rays[i].next_touch_y;
			break ;
		}
		rays[i].next_touch_x += rays[i].xstep;
		rays[i].next_touch_y += rays[i].y_step;
	}
}

int	its_a_wall2(double x, double y, t_player *player)
{
	int	check_x;
	int	check_y ;

	check_x = x / 64;
	check_y = y / 64;
	if (player->staticarray[check_y][check_x] == '1')
		return (1);
	else
		return (0);
}
