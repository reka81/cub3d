#include "cub3d.h"

uint32_t	find_color(t_ray *ray, int y,
				int wallheight, uint32_t *wall_texture, t_texture *texture)
{
	int			TextureOffsetX;
	int			distance_from_top;
	int			textureOffsetY;
	uint32_t	color;

	TextureOffsetX = ray->hit_vertical ? (int)ray->wallhity % texture->width : (int)ray->wallhitx % texture->width;
	distance_from_top = y - ((64 * 10) / 2) + (wallheight / 2);
	if (wallheight == 0)
		textureOffsetY = 0;
	else
		textureOffsetY = (distance_from_top * texture->height) / wallheight;
	if (textureOffsetY < 0)
		textureOffsetY = 0;
	if (textureOffsetY >= texture->height)
		textureOffsetY = texture->height - 1;
	color = wall_texture[textureOffsetY * texture->width + TextureOffsetX];
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

void	draw(t_ray *ray, int i, t_player *player,
			t_texture *texture, int wallheight)
{
	uint32_t	*wall_texture;
	int			wall_top;
	int			wall_bottom;
	uint32_t	color;
	int			y;

	wall_bottom = (SCREEN_HEIGHT / 2) + (wallheight / 2);
	wall_top = (SCREEN_HEIGHT / 2) - (wallheight / 2);
	wall_texture = wall_draw_3d_2(ray, i, player);
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom >= SCREEN_HEIGHT)
		wall_bottom = SCREEN_HEIGHT - 1;
	y = 0;
	while (y < wall_top)
		put_pixel_to_buffer(player->buffer, i, y++, 0x87CEEB, player->size_line, player->bits_per_pixel);
	while (y <= wall_bottom)
	{
		color = find_color(&ray[i], y, wallheight, wall_texture, texture);
		put_pixel_to_buffer(player->buffer, i, y++, color, player->size_line, player->bits_per_pixel);
    }
	while (y < SCREEN_HEIGHT)
		put_pixel_to_buffer(player->buffer, i, y++, 0x808080, player->size_line, player->bits_per_pixel);
}
