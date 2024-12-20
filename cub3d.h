#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>


#define FOV_ANGLE (60 * (M_PI / 180))

typedef struct s_ray{
    double ray_angle;
    double wallhitx;
    double wallhity;
    double vertwallhitx;
    double vertwallhity;
    int downward_ray;
    int upward_ray;
    int left_ray;
    int right_ray;
    double distance;
    int hit_vertical;
    //new
    double x_interecept;
    double y_interecept;
    double xstep;
    double y_step;
    double next_touch_y;
    double next_touch_x;
    int wall_found;
    int vert_wall_found;
}t_ray;
typedef struct s_player{
    double x;
    double y;
    int radius;
    int turn_direction;
    int walkdirection;
    double rotationAngle;
    int movespeed;
    double rotationspeed;
    char (*staticArray)[17];
    void *mlx;
    void *win;
    t_ray *rays;
}t_player;


void draw_player(t_player *player, void *win, void *mlx);
int update_player2(int keycode, t_player *player);
int update_player(int keycode ,t_player *player);
int update_map(t_player *player);
t_ray *cast_rays(t_player *player);
void render(t_player * player, t_ray *ray, int j);
void draw_player(t_player *player, void *win, void *mlx);
void player_init(t_player *player, char staticArray[10][17], void *mlx, void *win);
int its_a_wall(double x, double y, t_player *player);
void draw_line(t_player *player, void *mlx , void *win);
void draw_image(char staticArray[10][17] , void *mlx , void*win);

#endif