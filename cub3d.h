#ifndef CUB3D_H
#define CUB3D_H

#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include "parsing.h"

#define SCREEN_HEIGHT (64 * 10)
#define SCREEN_WIDTH (64 * 15)
#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64


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
    bool north_face;
	bool south_face;
	bool east_face;
	bool west_face;
}t_ray;
typedef struct s_texture
{
    void    *img;
    char    *data;
    int     width;
    int     height;
    int     bpp;
    int     size_line;
    int     endian;
} t_texture;
typedef struct s_player{
    void * buffer;
    int size_line;
    int bits_per_pixel;
    void *img;
    double x;
    double y;
    int radius;
    int turn_direction;
    int walkdirection;
    double rotationAngle;
    int movespeed;
    double rotationspeed;
    int get_num_rows;
    int longest_row;
    char (*staticArray)[32];
    void *mlx;
    void *win;
    t_ray *rays;
    t_texture *texture;
    t_texture **textures;
}t_player;


void draw_player(t_player *player, void *win, void *mlx);
int update_player2(int keycode, t_player *player);
int update_player(int keycode ,t_player *player);
int update_map(t_player *player);
t_ray *cast_rays(t_player *player);
void render(t_player * player, t_ray *ray, int j);
void draw_player(t_player *player, void *win, void *mlx);
void player_init(t_player *player, char map[15][32], void *mlx, void *win);
int its_a_wall(double x, double y, t_player *player);
void put_pixel_to_buffer(char *buffer, int x, int y, int color, int size_line, int bits_per_pixel);
void draw_line(t_player *player, void *mlx , void *win);
void draw_image(char staticArray[10][17] , void *mlx , void*win, void *img, char* buffer, int size_line, int bits_per_pizel);
t_strings *retrieving(int ac, char **av);
#endif