/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:39:29 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/29 13:28:25 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_vertical_inter2(t_ray *rays, int i)
{
	rays[i].y_step = 0;
	rays[i].xstep = 0;
	rays[i].next_touch_y = 0;
	rays[i].next_touch_x = 0;
	rays[i].x_interecept = 0;
	rays[i].y_interecept = 0;
	rays[i].vert_wall_found = 0;
}

void	check_vertical_inter3(t_ray *rays, t_player *player, int i)
{
	rays[i].x_interecept = floor(player->x / 64) * 64;
	if (rays[i].right_ray == 1)
		rays[i].x_interecept += 64;
	rays[i].y_interecept = player->y + (player->x - rays[i].x_interecept)
		* tan(rays[i].ray_angle);
	rays[i].xstep = 64;
	if (rays[i].left_ray == 1)
		rays[i].xstep *= -1;
	rays[i].y_step = 64 * tan(rays[i].ray_angle);
	if (rays[i].upward_ray == 1 && rays[i].y_step > 0)
		rays[i].y_step *= -1;
	if (rays[i].downward_ray == 1 && rays[i].y_step < 0)
		rays[i].y_step *= -1;
}

void	check_vertical_inter(t_player *player, t_ray *rays, int i)
{
	double	x_check;

	check_vertical_inter2(rays, i);
	check_vertical_inter3(rays, player, i);
	rays[i].next_touch_x = rays[i].x_interecept;
	rays[i].next_touch_y = rays[i].y_interecept;
	while (rays[i].next_touch_x >= 0 && rays[i].next_touch_x <= 64
		* player->longest_row && rays[i].next_touch_y >= 0
		&& rays[i].next_touch_y <= 64 * player->get_num_rows)
	{
		x_check = rays[i].next_touch_x;
		if (rays[i].left_ray == 1)
			x_check--;
		if (its_a_wall2(x_check, rays[i].next_touch_y, player))
		{
			rays[i].vert_wall_found = 1;
			rays[i].vertwallhitx = rays[i].next_touch_x;
			rays[i].vertwallhity = rays[i].next_touch_y;
			break ;
		}
		rays[i].next_touch_x += rays[i].xstep;
		rays[i].next_touch_y += rays[i].y_step;
	}
}

void	ray_casting2(t_ray *rays, int i)
{
	rays[i].x_interecept = 0;
	rays[i].y_interecept = 0;
	rays[i].xstep = 0;
	rays[i].y_step = 0;
	rays[i].next_touch_y = 0;
	rays[i].next_touch_x = 0;
	rays[i].wall_found = 0;
	rays[i].north_face = false;
	rays[i].south_face = false;
	rays[i].east_face = false;
	rays[i].west_face = false;
}

void	ray_casting3(double horizontal_hit, double vertical_hit,
			t_ray *rays, int i)
{
	printf("%f--%f\n",horizontal_hit, vertical_hit);
	if (horizontal_hit < vertical_hit)
	{
		rays[i].distance = horizontal_hit;
		rays[i].hit_vertical = 0;
		rays[i].wallhitx = rays[i].wallhitx;
		rays[i].wallhity = rays[i].wallhity;
	}
	else
	{
		rays[i].distance = vertical_hit;
		rays[i].hit_vertical = 1;
		rays[i].wallhitx = rays[i].vertwallhitx;
		rays[i].wallhity = rays[i].vertwallhity;
	}
}
