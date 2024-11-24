#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct s_player{
    int x;
    int y;
    int radius;
    int turn_direction;
    int walkdirection;
    double rotationAngle;
    int movespeed;
    int rotationspeed;
    char (*staticArray)[17];
    void *mlx;
    void *win;
}t_player;

void draw_image(char staticArray[10][17] , void *mlx , void*win)
{
    int i = 0;
    int j = 0;
   while (i < 10)
    {
        j = 0;
        while(staticArray[i][j] != '\n')
        {
            int color;
            int y = 0;
            if(staticArray[i][j] == '1')
                color = 0xFF0000;
            if(staticArray[i][j] == '0')
                color = 0x000000;
            int x;
            while(y < 32)
            {
                x = 0;
                while (x < 32)
                {
                    mlx_pixel_put(mlx, win, j * 32 + x , i * 32 + y, color);
                    x++;
                }
                mlx_pixel_put(mlx, win, j *32 + x - 1, i*32 + y, 0xFFFFFF);
                y++;
            }
            x = 0;
            while (x < 32)
            {
                mlx_pixel_put(mlx, win, j * 32 + x, i *32 + y - 1, 0xFFFFFF);
                x++;
            }
            j++;
        }
        i++;
    }
}
void draw_line(t_player *player, void*win, void *mlx)
{
    int x = player->x;
    int y = player->y;
    int i = 0;
    while (i <  30)
    {
        x += cos(player->rotationAngle);
        y += sin(player->rotationAngle);
        mlx_pixel_put(mlx, win, x, y, 0xFFFFFF);
        i++;
    }
    
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
                x = player->x + i;
                y = player->y + j;
                if ((i * i + j * j) <= (player->radius * player->radius))
                    mlx_pixel_put(mlx, win, x, y , 0xFFFFFF); // square_understand
            j++;
            }
        i++;
    }
    draw_line(player, win, mlx);
}

int update_player(int keycode ,t_player *player)
{
    
}
int update_map(t_player *player)
{
    draw_image(player->staticArray, player->mlx, player->win);
    draw_player(player, player->win, player->mlx);
    return(0);
}
void player_init(t_player *player, char staticArray[10][17], void *mlx, void *win)
{
    player->x = 32 * 15 /2;
    player->y = 32 * 10 /2;
    player->radius = 8;
    player->turn_direction = 0;
    player->walkdirection = 0;
    player->rotationAngle = M_PI / 2;
    player->movespeed = 2.0;
    player->rotationspeed = 2 * (M_PI / 2);
    player->staticArray = staticArray;
    player->win = win;
    player->mlx = mlx;

}
int main()
{
    void *mlx;
    void *win;
    t_player *player;
    char staticArray[10][17] = {
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' , '\n', '\0'}, // Row 1
        {'1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' , '\n', '\0'}, // Row 2
        {'1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '1', '1', '0', '0', '1' , '\n', '\0'}, // Row 3
        {'1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '1', '1', '0', '0', '1' , '\n', '\0'}, // Row 4
        {'1', '0', '0', '0', '1', '1', '0', '0', '0', '1', '1', '1', '0', '0', '1' , '\n', '\0'}, // Row 5
        {'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1' , '\n', '\0'}, // Row 6
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' , '\n', '\0'}, // Row 7
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' , '\n', '\0'}, // Row 8
        {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1' , '\n', '\0'}, // Row 9
        {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' , '\n', '\0'}  // Row 10
    };

    player = malloc(sizeof(t_player));
    mlx = mlx_init();
    win = mlx_new_window(mlx, 32 * 15, 32 * 10, "window");
    player_init(player, staticArray, mlx, win);
    draw_image(staticArray, mlx, win);
    draw_player(player, win, mlx);
    mlx_hook(win, 2, 0, &update_player, player);
    mlx_loop_hook(mlx, &update_map, player);
    mlx_loop(mlx);
}