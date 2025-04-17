#include "cub3d.h"
uint32_t find_color(t_ray *ray, int y, int wallheight, uint32_t *wall_texture, t_texture *texture) {
    int TextureOffsetX = ray->hit_vertical ? (int)ray->wallhity % texture->width : (int)ray->wallhitx % texture->width;

    int distance_from_top = y - ((64 * 10) / 2) + (wallheight / 2);
    int textureOffsetY;
    if (wallheight == 0) {
    textureOffsetY = 0;  // Or some fallback value, depending on what makes sense
    } else {
        textureOffsetY = (distance_from_top * texture->height) / wallheight;
    }

    if (textureOffsetY < 0) textureOffsetY = 0;
    if (textureOffsetY >= texture->height) textureOffsetY = texture->height - 1;

    uint32_t color = wall_texture[textureOffsetY * texture->width + TextureOffsetX];
    return color;
}

void wall_draw_3d(int rays_num, t_ray *ray, void *win, void *mlx, t_player *player, t_texture *texture) {
    
    int i = 0;
    int wallheight = 0;
    int distanceProjectionPlane = (SCREEN_WIDTH / 2) / tan(FOV_ANGLE / 2);
    uint32_t *wall_texture;
    while (i < rays_num) {
        float corrected_distance = ray[i].distance * cos(ray[i].ray_angle - player->rotationAngle);
        wallheight = (TEXTURE_HEIGHT / corrected_distance) * distanceProjectionPlane;

        wallheight *= (float)SCREEN_WIDTH / SCREEN_HEIGHT;
        if(ray[i].north_face)
            wall_texture = (uint32_t *)player->texture->data;
        if(ray[i].south_face)
            wall_texture = (uint32_t *)player->textures[1]->data;
        if(ray[i].west_face)
            wall_texture = (uint32_t *)player->textures[3]->data;
        if(ray[i].east_face)
            wall_texture = (uint32_t *)player->textures[2]->data;
        int wall_top = (SCREEN_HEIGHT / 2) - (wallheight / 2);
        int wall_bottom = (SCREEN_HEIGHT / 2) + (wallheight / 2);

        if (wall_top < 0) wall_top = 0;
        if (wall_bottom >= SCREEN_HEIGHT) wall_bottom = SCREEN_HEIGHT - 1;
        for (int y = 0; y < wall_top; y++) {
            put_pixel_to_buffer(player->buffer, i, y, 0x87CEEB, player->size_line, player->bits_per_pixel);
        }

        for (int y = wall_top; y <= wall_bottom; y++) {
            uint32_t color = find_color(&ray[i], y, wallheight, wall_texture, texture);
            put_pixel_to_buffer(player->buffer, i, y, color, player->size_line, player->bits_per_pixel);
        }

        for (int y = wall_bottom + 1; y < SCREEN_HEIGHT; y++) {
            put_pixel_to_buffer(player->buffer, i, y, 0x808080, player->size_line, player->bits_per_pixel);
        }

        i++;
    }
    mlx_put_image_to_window(mlx, win, player->img, 0, 0);
}



int update_map(t_player *player)
{
    double step = 0.0;
    double next_player_x ;
    double next_player_y ;
    int i;
    i = 0;
    t_ray *ray = NULL;

    next_player_x = 0.0;
    next_player_y = 0.0;
    step = player->walkdirection * player->movespeed;
    player->rotationAngle += player->turn_direction * player->rotationspeed;
    
    next_player_x = player->x + cos(player->rotationAngle) * step;
    next_player_y = player->y - sin(player->rotationAngle) * step;
    if(!its_a_wall(next_player_x, next_player_y, player))
    {
        player->x = next_player_x;
        player->y = next_player_y;
    }
    if (player->rotationAngle < 0)
        player->rotationAngle += 2 * M_PI;
    if (player->rotationAngle > 2 * M_PI)    
        player->rotationAngle -= 2 * M_PI;
    ray = cast_rays(player);
    wall_draw_3d(64 * player->longest_row, ray, player->win, player->mlx, player, player->texture);
    player->rays = ray;

    return(0);
}