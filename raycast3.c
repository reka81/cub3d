/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:44:36 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/26 10:53:24 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	rays = (t_ray *)zyalloc(sizeof(t_ray) * 64 * player->longest_row);
	ray_angle = player->rotationangle + M_PI / 6.0;
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
