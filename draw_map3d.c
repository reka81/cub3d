/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map3d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mettalbi <mettalbi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:49:08 by mettalbi          #+#    #+#             */
/*   Updated: 2025/04/25 12:14:36 by mettalbi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

uint32_t	find_color(t_ray *ray, int y,
				t_wall_clumper *info, t_texture *texture)
{
	int			textureoffsetx;
	int			distance_from_top;
	int			textureoffsety;
	uint32_t	color;

	if (ray->hit_vertical)
		textureoffsetx = (int)ray->wallhity % texture->width;
	else
		textureoffsetx = (int)ray->wallhitx % texture->width;
	distance_from_top = y - ((64 * 10) / 2) + (info->wallheight / 2);
	if (info->wallheight == 0)
		textureoffsety = 0;
	else
		textureoffsety = (distance_from_top * texture->height)
			/ info->wallheight;
	if (textureoffsety < 0)
		textureoffsety = 0;
	if (textureoffsety >= texture->height)
		textureoffsety = texture->height - 1;
	color = info->wall_texture[textureoffsety
		* texture->width + textureoffsetx];
	return (color);
}

uint32_t	*wall_draw_3d_2(t_ray *ray, int i, t_player *player)
{
	uint32_t	*wall_texture;

	if (ray[i].north_face)
		wall_texture = (uint32_t *)player->texture->data;
	if (ray[i].south_face)
		wall_texture = (uint32_t *)player->textures[1]->data;
	if (ray[i].west_face)
		wall_texture = (uint32_t *)player->textures[3]->data;
	if (ray[i].east_face)
		wall_texture = (uint32_t *)player->textures[2]->data;
	return (wall_texture);
}

int	draw_mid(int y, t_wall_clumper *info, t_player *player, t_ray *ray)
{
	uint32_t		color;

	y = 0;
	while (y < info->wall_top)
	{
		put_pixel_to_buffer(info->i, y, player->c_color, player);
		y++;
	}
	while (y <= info->wall_bottom)
	{
		color = find_color(&ray[info->i], y, info, player->texture);
		put_pixel_to_buffer(info->i, y, color, player);
		y++;
	}
	return (y);
}

void	draw(t_ray *ray, int i, t_player *player, int wallheight)
{
	uint32_t		*wall_texture;
	int				y;
	t_wall_clumper	*info;

	info = malloc(sizeof(t_wall_clumper));
	info->wall_bottom = (SCREEN_HEIGHT / 2) + (wallheight / 2);
	info->wall_top = (SCREEN_HEIGHT / 2) - (wallheight / 2);
	wall_texture = wall_draw_3d_2(ray, i, player);
	info->wall_texture = wall_texture;
	info->wallheight = wallheight;
	info->i = i;
	if (info->wall_top < 0)
		info->wall_top = 0;
	if (info->wall_bottom >= SCREEN_HEIGHT)
		info->wall_bottom = SCREEN_HEIGHT - 1;
	y = draw_mid(y, info, player, ray);
	while (y < SCREEN_HEIGHT)
	{
		put_pixel_to_buffer(i, y, player->f_color, player);
		y++;
	}
}
