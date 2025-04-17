#include "cub3d.h"

void draw_line(t_player *player, void *mlx , void *win)
{
    (void)mlx;
    (void)win;
    int line_length = 30;

    mlx_pixel_put(player->mlx, player->win, player->x, player->y, 0xFFFFFF);
    for (int i = 0; i <= line_length; i++) {
        double pixel_x = player->x + cos(player->rotationAngle) * i;
        double pixel_y = player->y - sin(player->rotationAngle) * i;
        mlx_pixel_put(player->mlx, player->win, (int)pixel_x, (int)pixel_y, 0xFF0000);
    }
}

int its_a_wall(double x, double y, t_player *player)
{
    
    int check_x = x / 64;
    int check_y = y / 64;
    if(player->staticArray[check_y][check_x] == '1')
        return(1);
    else
        return(0);
}

void player_init(t_player *player, char **staticArray, void *mlx, void *win)
{
    // player->x = 64 * player->longest_row /2;
    // player->y = 64 * player->get_num_rows /2;
    // printf("%d--%d\n",  player->longest_row /2, player->get_num_rows /2);
    player->radius = 9;
    player->turn_direction = 0;
    player->walkdirection = 0;
    player->rotationAngle = M_PI / 2;
    player->movespeed = 6.0;
    player->rotationspeed = (M_PI / 25);
    player->staticArray = staticArray;
    player->win = win;
    player->mlx = mlx;
}

void draw_player(t_player *player, void *win, void *mlx)
{
    int i = -player->radius;
    int j = -player->radius;
    int x= 0;
    int y = 0;
    while(i < player->radius)
    {
        j = -player->radius;
            while (j < player->radius)
            {
                x = (player->x) + i;
                y = (player->y) + j;
                if ((i * i + j * j) <= (player->radius * player->radius))
                    put_pixel_to_buffer(player->buffer, x, y, 0xFFFFFF, player->size_line, player->bits_per_pixel);
            j++;
            }
        i++;
    }
    mlx_put_image_to_window(mlx, win, player->img, 0, 0);
}
