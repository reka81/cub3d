#include "cub3d.h"
void draw_ray_lines(t_player * player, t_ray *ray, int j)
{
    int line_length = 64 * 15;

    mlx_pixel_put(player->mlx, player->win, player->x, player->y, 0xffff00); 
    for (int i = 0; i <= line_length; i++) {
        double pixel_x = player->x + cos(ray[j].ray_angle) * i;
        double pixel_y = player->y - sin(ray[j].ray_angle) * i;
        mlx_pixel_put(player->mlx, player->win, (int)pixel_x, (int)pixel_y, 0xffff00); 
    }
}
double distance_between(double player_x, double player_y, double wall_hitx, double wall_hity)
{
    return(sqrt((player_x - wall_hitx) * (player_x - wall_hitx) + (player_y - wall_hity) * (player_y - wall_hity)));
}
void check_horizontal_inter(t_player *player, t_ray *rays, int i)
{
    rays[i].y_step = 0;
    rays[i].xstep = 0;
    rays[i].next_touch_y = 0;
    rays[i].next_touch_x = 0;
    rays[i].x_interecept = 0;
    rays[i].y_interecept = 0;
    rays[i].wall_found = 0;
    rays[i].y_interecept = floor(player->y / 64) * 64;
    if(rays[i].downward_ray == 1)
        rays[i].y_interecept += 64;
    rays[i].x_interecept = player->x + (player->y - rays[i].y_interecept) / tan(rays[i].ray_angle);
    rays[i].y_step = 64;
    if(rays[i].upward_ray == 1)
        rays[i].y_step *= - 1;
    rays[i].xstep = 64 / tan(rays[i].ray_angle);
    if(rays[i].left_ray == 1 && rays[i].xstep > 0)
        rays[i].xstep *= -1;
    if(rays[i].right_ray == 1 && rays[i].xstep < 0)
        rays[i].xstep *= -1;
    rays[i].next_touch_x = rays[i].x_interecept;
    rays[i].next_touch_y = rays[i].y_interecept;
    while(rays[i].next_touch_x >= 0 && rays[i].next_touch_x <= 64 * 15 && rays[i].next_touch_y >= 0 && rays[i].next_touch_y <= 64 * 10)
    {
        double y_check = rays[i].next_touch_y;
        if (rays[i].upward_ray == 1)
        {
            y_check--;      
        }
        if(its_a_wall(rays[i].next_touch_x,  y_check, player) || rays[i].next_touch_y == 64)
        {
            rays[i].wall_found = 1;
            rays[i].wallhitx = rays[i].next_touch_x;
            rays[i].wallhity =rays[i].next_touch_y;
            break;
        }
        rays[i].next_touch_x += rays[i].xstep;
        rays[i].next_touch_y += rays[i].y_step;
    }
}
int its_a_wall2(double x, double y, t_player *player)
{
    int check_x = x / 64;
    int check_y = y / 64;

    if(player->staticArray[check_y][check_x] == '1')
        return(1);
    else
        return(0);
}

void check_vertical_inter(t_player *player, t_ray *rays, int i)
{
    double x_check;
    rays[i].y_step = 0;
    rays[i].xstep = 0;
    rays[i].next_touch_y = 0;
    rays[i].next_touch_x = 0;
    rays[i].x_interecept = 0;
    rays[i].y_interecept = 0;
    rays[i].vert_wall_found = 0;
    
    rays[i].x_interecept = floor(player->x / 64) * 64;
    if(rays[i].right_ray == 1)
        rays[i].x_interecept += 64;
    rays[i].y_interecept = player->y + (player->x - rays[i].x_interecept) * tan(rays[i].ray_angle);
    rays[i].xstep = 64;
    if(rays[i].left_ray == 1)  
        rays[i].xstep *= -1;
    rays[i].y_step = 64 * tan(rays[i].ray_angle);
    if(rays[i].upward_ray == 1 && rays[i].y_step > 0) 
        rays[i].y_step *= -1;
    if(rays[i].downward_ray == 1 && rays[i].y_step < 0)
        rays[i].y_step *= -1;
    rays[i].next_touch_x = rays[i].x_interecept;
    rays[i].next_touch_y = rays[i].y_interecept;
    while(rays[i].next_touch_x >= 0 && rays[i].next_touch_x <= 64 * 15 && rays[i].next_touch_y >= 0 && rays[i].next_touch_y <= 64 * 10)
    {
        x_check = rays[i].next_touch_x;
        if (rays[i].left_ray == 1)
            x_check--;

        if(its_a_wall2(x_check, rays[i].next_touch_y, player))
        {
            rays[i].vert_wall_found = 1;
            rays[i].vertwallhitx = rays[i].next_touch_x;
            rays[i].vertwallhity = rays[i].next_touch_y;
            break;
        }
        rays[i].next_touch_x += rays[i].xstep;
        rays[i].next_touch_y += rays[i].y_step;
    }
}
void ray_casting(t_player *player , int i, t_ray *rays)
{
     rays[i].x_interecept = 0;
     rays[i].y_interecept = 0;
     rays[i].xstep = 0;
     rays[i].y_step = 0;
     rays[i].next_touch_y = 0;
     rays[i].next_touch_x = 0;
     rays[i].wall_found = 0;
    check_vertical_inter(player, rays, i);
    check_horizontal_inter(player, rays, i);
    double horizontal_hit = 0;
    double vertical_hit = 0;

    if(rays[i].wall_found == 1)
        horizontal_hit = distance_between(player->x, player->y, rays[i].wallhitx, rays[i].wallhity);
    else
        horizontal_hit = 2147483647; 
    if(rays[i].vert_wall_found == 1)
        vertical_hit = distance_between(player->x, player->y, rays[i].vertwallhitx, rays[i].vertwallhity);
    else
        vertical_hit = 2147483647; 
    if(rays[i].wallhitx > rays[i].vertwallhitx)
        rays[i].wallhitx = rays[i].vertwallhitx;
    if(rays[i].wallhity > rays[i].vertwallhity)
        rays[i].wallhity = rays[i].vertwallhity;
    if(horizontal_hit > vertical_hit)
    {
        rays[i].distance = vertical_hit;
        rays[i].hit_vertical = 1;
    }
    else
    {
        rays[i].distance = horizontal_hit;
        rays[i].hit_vertical = 0;
    }
}




void render(t_player * player, t_ray *ray, int j)
{
     j =0;
    while(j < 64 * 15)
    {
        float line_length = ray[j].distance ;  
        (void)j;
        (void)ray;
        put_pixel_to_buffer(player->buffer, player->x, player->y, 0xFFFF00, player->size_line, player->bits_per_pixel);
    // printf("distance = %f\n", line_length);
        for (int i = 0; i <= line_length; i++) {
            double pixel_x = (player->x ) + cos(ray[j].ray_angle) * i;
            double pixel_y = (player->y) - sin(ray[j].ray_angle) * i;
            put_pixel_to_buffer(player->buffer, pixel_x, pixel_y, 0xFFFF00, player->size_line, player->bits_per_pixel);
        }
        j++;
    }
    mlx_put_image_to_window(player->mlx, player->win, player->img, 0, 0);
}

t_ray *cast_rays(t_player *player) {
    t_ray * rays;
    int column = 0;
    int i = 0;
    double ray_angle = 0.0;
    rays = (t_ray *)malloc(sizeof(t_ray) * 64 * 15);
    
    ray_angle = player->rotationAngle + M_PI / 6.0;
    while(i <  64 * 15)
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
        player->rays = rays;
        ray_angle -= (M_PI / (3.0 * 60 * 15));
        i++;
        column++;
    }
        player->rays = rays;
        render(player, player->rays, i);
    return(rays);
}