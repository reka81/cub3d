#include "cub3d.h"
void draw_ray_lines(t_player * player, t_ray *ray, int j)
{
    int line_length = 32 * 15;

    mlx_pixel_put(player->mlx, player->win, player->x, player->y, 0xffff00); 
    for (int i = 0; i <= line_length; i++) {
        double pixel_x = player->x + cos(ray[j].ray_angle) * i;
        double pixel_y = player->y - sin(ray[j].ray_angle) * i;
        mlx_pixel_put(player->mlx, player->win, (int)pixel_x, (int)pixel_y, 0xffff00); 
    }
}

void ray_casting(t_player *player , int i, t_ray *rays)
{
    int x_interecept = 0;
    int y_interecept = 0;
    int xstep = 0;
    int y_step = 0;
    int next_touch_y = 0;
    int next_touch_x = 0;
    int wall_found = 0;
    // printf("right:%d--left:%d---down:%d---up:%d\n", rays[i].right_ray, rays[i].left_ray, rays[i].downward_ray, rays[i].upward_ray);
    // printf("%d\n", i);
    y_interecept = (player->y / 32) * 32;
    if(rays[i].downward_ray == 1)
        y_interecept += 32;
    x_interecept = player->x + (player->y - y_interecept) / tan(rays[i].ray_angle);
    y_step = 32;
    if(rays[i].upward_ray == 1)
        y_step *= - 1;
    xstep = 32 / tan(rays[i].ray_angle);
    if(rays[i].left_ray == 1 && xstep > 0)
        xstep *= -1;
    if(rays[i].right_ray == 1 && xstep < 0)
        xstep *= -1;
    next_touch_x = x_interecept;
    next_touch_y = y_interecept;
    if (rays[i].upward_ray == 1)
        next_touch_y--;
    while(next_touch_x >= 0 && next_touch_x <= 32 * 15 && next_touch_y >= 0 && next_touch_y <= 32 * 10)
    {
        if(its_a_wall(next_touch_x, next_touch_y, player))
        {
            wall_found = 1;
            rays[i].wallhitx = next_touch_x;
            rays[i].wallhity = next_touch_y;
            printf("%d---%d\n", next_touch_x / 32, next_touch_y / 32);
            // draw_ray_lines(player, rays, i);
            break;
        }
        next_touch_x += xstep;
        next_touch_y += y_step;
    }
}


void render(t_player * player, t_ray *ray, int j)
{
    int line_length = 40;  

    mlx_pixel_put(player->mlx, player->win, player->x, player->y, 0xffff00); 
    for (int i = 0; i <= line_length; i++) {
        double pixel_x = player->x + cos(ray[j].ray_angle) * i;
        double pixel_y = player->y - sin(ray[j].ray_angle) * i;
        mlx_pixel_put(player->mlx, player->win, (int)pixel_x, (int)pixel_y, 0xffff00); 
    }
}
t_ray *cast_rays(t_player *player) {
    t_ray * rays;
    int column = 0;
    int i = 0;
    double ray_angle = 0.0;
    rays = malloc(sizeof(t_player) * 700);

    ray_angle = player->rotationAngle -  FOV_ANGLE / 2;
    while(i < 1)
    {
        ray_angle = fmod(ray_angle, 2 * M_PI);        
        if (ray_angle < 0) {
            ray_angle += 2 * M_PI;
        }
        if (ray_angle > 0 && ray_angle < M_PI)
            rays[i].downward_ray = 0;
        else
            rays[i].downward_ray = 1;
        rays[i].upward_ray = !rays[i].downward_ray;
        if(ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI)
            rays[i].right_ray = 1;
        else
            rays[i].right_ray = 0;
        rays[i].left_ray = !rays[i].right_ray;
        rays[i].ray_angle = ray_angle;
        ray_casting(player, i, rays);
        ray_angle += FOV_ANGLE / (32 * 15);
        i++;
        column++;
    }
    return(rays);
}