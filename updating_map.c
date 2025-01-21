#include "cub3d.h"
void wall_draw_3d(int rays_num , t_ray * ray, void *win, void *mlx, t_player *player)
{
    int i = 0;
    int wallheight = 0;
    int distanceProjectionPlane = (32 * 15) / tan(FOV_ANGLE / 2);
    while (i < rays_num)
    {
        wallheight = (32 / (ray[i].distance * cos(ray[i].ray_angle - player->rotationAngle))) * distanceProjectionPlane;
                int wall_top = (32 * 10 / 2) - (wallheight / 2);
        int wall_bottom = (32 *10 / 2) + (wallheight / 2);

        // Clamp values to screen
        if (wall_top < 0) wall_top = 0;
        if (wall_bottom >= 32 *10) wall_bottom = 32 *10 - 1;

        // Draw the wall slice (vertical line) at column i
        for (int y = 0; y < wall_top; y++)
        {
            mlx_pixel_put(mlx, win, i, y, 0x87CEEB); // Sky color (light blue)
        }
        
        int y = wall_top;

        while (y <= wall_bottom)
        {
            int color = 0xA0522D; // Example color, white
            mlx_pixel_put(mlx, win, i, y, color);
            y++;
        }
        y = wall_bottom + 1;
        while (y < 32 * 10)
        {
            mlx_pixel_put(mlx, win, i, y, 0x808080); // Floor color (sea green)
            y++;
        }
        i++;
    }
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
    mlx_clear_window(player->mlx, player->win);
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
    ray = cast_rays(player);
    wall_draw_3d(32 * 15, ray, player->win, player->mlx, player);
    draw_image(player->staticArray, player->mlx, player->win);
    draw_player(player, player->win, player->mlx);
    player->rays = ray;
 
    return(0);
}