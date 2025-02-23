#include "cub3d.h"
void wall_draw_3d(int rays_num, t_ray *ray, void *win, void *mlx, t_player *player, t_texture *texture) {
    int i = 0;
    int wallheight = 0;
    int distanceProjectionPlane = (64 * 15) / tan(FOV_ANGLE / 2);
    int texX = 0;

    while (i < rays_num) {
        // Calculate wall height based on distance and projection
        wallheight = (64 / (ray[i].distance * cos(ray[i].ray_angle - player->rotationAngle))) * distanceProjectionPlane;
        int wall_top = (64 * 10 / 2) - (wallheight / 2);
        int wall_bottom = (64 * 10 / 2) + (wallheight / 2);

        // Clamp values to screen
        if (wall_top < 0) wall_top = 0;
        if (wall_bottom >= 64 * 10) wall_bottom = 64 * 10 - 1;

        // Calculate the hit position on the wall
        double hit_x, hit_y;
        if (ray[i].hit_vertical == 1) {
            hit_x = player->y + ray[i].distance * sin(ray[i].ray_angle);
            hit_y = player->x + ray[i].distance * cos(ray[i].ray_angle);
        } else {
            hit_x = player->x + ray[i].distance * cos(ray[i].ray_angle);
            hit_y = player->y + ray[i].distance * sin(ray[i].ray_angle);
        }

        // Convert hit position to grid coordinates
        int grid_x = (int)(hit_x / 64); // Using 64 directly for grid index
        int grid_y = (int)(hit_y / 64); // Using 64 directly for grid index

        // Determine wall texture based on grid coordinates

        // Calculate texture X coordinate
        double wallX = (hit_x - grid_x * 64) / 64; // Normalized hit position in the tile
        texX = (int)(wallX * (double)texture->width);
        if ((ray[i].hit_vertical == 1 && ray[i].right_ray == 1) || (ray[i].hit_vertical == 0 && ray[i].left_ray == 1))
            texX = texture->width - texX - 1;

        // Draw ceiling
        for (int y = 0; y < wall_top; y++) {
            put_pixel_to_buffer(player->buffer, i, y, 0x87CEEB, player->size_line, player->bits_per_pixel);
        }

        // Draw wall with texture
        int y = wall_top;
        int color = 0;
        while (y <= wall_bottom) {
            int texY = (int)(((y - wall_top) / (float)(wall_bottom - wall_top)) * texture->height);
            
            texY = fmin(texY, texture->height - 1);
            if ((texY * texture->size_line + texX * (texture->bpp / 8)) < 0 || 
                    (texY * texture->size_line + texX * (texture->bpp / 8)) >= texture->width * texture->height * (texture->bpp / 8)) {
                color = 0; // Use a default color if out of bounds
                y++;
                continue; // Skip this pixel
            }
            color = *(int *)(texture->data + (texY * texture->size_line + texX * (texture->bpp / 8)));
            put_pixel_to_buffer(player->buffer, i, y, color, player->size_line, player->bits_per_pixel);
            y++;
        }

        // Draw floor
        y = wall_bottom + 1;
        while (y < 64 * 10) {
            put_pixel_to_buffer(player->buffer, i, y, 0x808080, player->size_line, player->bits_per_pixel);
            y++;
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
    // printf("%f--%d\n", (player->x), (next_player_x));
    // printf("%f--%\n", (player->y), (next_player_y));
    if(!its_a_wall(next_player_x, next_player_y, player))
    {
        player->x = next_player_x;
        player->y = next_player_y;
    }
    if (player->rotationAngle < 0)
        player->rotationAngle += 2 * M_PI;
    if (player->rotationAngle > 2 * M_PI)    
        player->rotationAngle -= 2 * M_PI;
    // printf("%p\n", ray);
    // ray = cast_rays(player);
    // draw_image(player->staticArray, player->mlx, player->win, player->img, player->buffer, player->size_line, player->bits_per_pixel);
    // draw_player(player, player->win, player->mlx);
    ray = cast_rays(player);
    wall_draw_3d(64 * 15, ray, player->win, player->mlx, player, player->texture);
    player->rays = ray;
    // mlx_clear_window(player->mlx, player->win);
 
    return(0);
}