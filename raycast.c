/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 14:39:29 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/19 17:44:42 by mettalbi         ###   ########.fr       */
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

void	ray_casting3(int horizontal_hit, int vertical_hit, t_ray *rays, int i)
{
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

void	ray_casting4(t_ray *rays, int i)
{
	if (!rays[i].hit_vertical)
	{
		if (rays[i].downward_ray)
			rays[i].south_face = true;
		else
			rays[i].north_face = true;
	}
	else
	{
		if (rays[i].right_ray)
			rays[i].east_face = true;
		else
			rays[i].west_face = true;
	}
}

void	ray_casting(t_player *player, int i, t_ray *rays)
{
	double	horizontal_hit;
	double	vertical_hit;

	ray_casting2(rays, i);
	check_vertical_inter(player, rays, i);
	check_horizontal_inter(player, rays, i);
	if (rays[i].wall_found)
		horizontal_hit = distance_between(player->x, player->y,
				rays[i].wallhitx, rays[i].wallhity);
	else
		horizontal_hit = INT_MAX;
	if (rays[i].vert_wall_found)
		vertical_hit = distance_between(player->x, player->y,
				rays[i].vertwallhitx, rays[i].vertwallhity);
	else
		vertical_hit = INT_MAX;
	ray_casting3(horizontal_hit, vertical_hit, rays, i);
	ray_casting4(rays, i);
}

void	cast_rays2(t_ray *rays, double ray_angle, int i)
{
	if (ray_angle > 0 && ray_angle < M_PI)
		rays[i].downward_ray = 0;
	else
		rays[i].downward_ray = 1;
	rays[i].upward_ray = !rays[i].downward_ray;
	if (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI)
		rays[i].right_ray = 1;
	else
		rays[i].right_ray = 0;
	rays[i].left_ray = !rays[i].right_ray;
	rays[i].ray_angle = ray_angle;
}

t_ray	*cast_rays(t_player *player)
{
	t_ray	*rays;
	int		column;
	int		i;
	double	ray_angle;

	i = 0;
	column = 0;
	rays = (t_ray *)malloc(sizeof(t_ray) * 64 * player->longest_row);
	ray_angle = player->rotationAngle + M_PI / 6.0;
	while (i < 64 * player->longest_row)
	{
		ray_angle = fmod(ray_angle, 2 * M_PI);
		cast_rays2(rays, ray_angle, i);
		ray_casting(player, i, rays);
		player->rays = rays;
		ray_angle -= (M_PI / (3.0 * 60 * player->longest_row));
		i++;
		column++;
	}
	player->rays = rays;
	return (rays);
}
