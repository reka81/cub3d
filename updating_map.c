#include "cub3d.h"

int update_map(t_player *player)
{
    double step = 0.0;
    double next_player_x ;
    double next_player_y ;
    int i;
    i = 0;
    t_ray *ray;

    next_player_x = 0.0;
    next_player_y = 0.0;
    mlx_clear_window(player->mlx, player->win);
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
    draw_image(player->staticArray, player->mlx, player->win);
    draw_player(player, player->win, player->mlx);
    ray = cast_rays(player);
    player->rays = ray;
    while (i < 1)    
    {
        render(player, player->rays, i);
        i++;
    }
    return(0);
}