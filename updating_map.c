/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updating_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:11:54 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/29 12:23:09 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	wall_draw_3d(int rays_num, t_ray *ray, t_player *player)
{
	int		i;
	int		wallheight;
	int		distanceprojectionplane;
	float	corrected_distance;

	i = 0;
	wallheight = 0;
	distanceprojectionplane = (SCREEN_WIDTH / 2) / tan((60 * (M_PI / 180)) / 2);
	while (i < rays_num)
	{
		corrected_distance = ray[i].distance
			* cos(ray[i].ray_angle - player->rotationangle);
		wallheight = (TEXTURE_HEIGHT / corrected_distance)
			* distanceprojectionplane;
		wallheight *= (float)SCREEN_WIDTH / SCREEN_HEIGHT;
		draw(ray, i, player, wallheight);
		i++;
	}
	mlx_put_image_to_window(player->mlx, player->win, player->img, 0, 0);
}

void	update_map2(t_player *player,
			double next_player_x, double next_player_y)
{
	if (!its_a_wall(next_player_x, next_player_y, player))
	{
		player->x = next_player_x;
		player->y = next_player_y;
	}
}

int	update_map(t_player *player)
{
	double	step;
	double	next_player_x ;
	double	next_player_y ;
	int		i;
	t_ray	*ray;

	i = 0;
	next_player_x = 0.0;
	next_player_y = 0.0;
	step = player->walkdirection * player->movespeed;
	player->rotationangle += player->turn_direction * player->rotationspeed;
	next_player_x = player->x + cos(player->rotationangle) * step;
	next_player_y = player->y - sin(player->rotationangle) * step;
	update_map2(player, next_player_x, next_player_y);
	if (player->rotationangle < 0)
		player->rotationangle += 2 * M_PI;
	if (player->rotationangle > 2 * M_PI)
		player->rotationangle -= 2 * M_PI;
	ray = cast_rays(player);
	wall_draw_3d(SCREEN_WIDTH, ray, player);
	player->rays = ray;
	return (0);
}
