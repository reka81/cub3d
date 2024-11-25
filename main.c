#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
}t_player;

int its_a_wall(double x, double y, t_player *player)
{
    int check_x = x / 32;
    int check_y = y / 32;
    printf("x:%d y:%d char:%c\n", check_x, check_y, player->staticArray[check_y][check_x]);
    if(player->staticArray[check_y][check_x] == '1')
        return(1);
    else
        return(0);
}

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
void draw_line(t_player *player, void *mlx , void *win)
{
    (void)mlx;
    (void)win;
    // player->rotationAngle += player->turn_direction *player->rotationspeed;
    int line_length = 30;  // Length of the line

    // Draw the line from player's position (x, y) to the calculated endpoint
    mlx_pixel_put(player->mlx, player->win, player->x, player->y, 0xFFFFFF); // Player position
    for (int i = 0; i <= line_length; i++) {
        double pixel_x = player->x + cos(player->rotationAngle) * i;
        double pixel_y = player->y - sin(player->rotationAngle) * i;
        mlx_pixel_put(player->mlx, player->win, (int)pixel_x, (int)pixel_y, 0xFF0000); // Line pixels
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

    // double step = 0.0;
    if (keycode == 123)
    {
        player->turn_direction = +1;
    }
    if (keycode == 124)
    {
        player->turn_direction = -1;
    }
    if (keycode == 126)
    {
        player->walkdirection = +1;
    }
    if (keycode == 125)
    {
        player->walkdirection = -1;
    }
    // step = player->walkdirection * player->movespeed;
    // player->rotationAngle += player->turn_direction * player->rotationspeed;
    // player->x += cos(player->rotationAngle) * step;
    // player->y -= sin(player->rotationAngle) * step;
        return(0);
}
int update_player2(int keycode, t_player *player)
{
    if (keycode == 123)
    {
        player->turn_direction = 0;
    }
    if (keycode == 124)
    {
        player->turn_direction = 0;
    }
    if(keycode == 125 || keycode == 126)
        player->walkdirection = 0;
    return(0);
}
int update_map(t_player *player)
{
    double step = 0.0;
    double next_player_x ;
    double next_player_y ;

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
    return(0);
}
void player_init(t_player *player, char staticArray[10][17], void *mlx, void *win)
{
    player->x = 32 * 15 /2;
    player->y = 32 * 10 /2;
    player->radius = 3;
    player->turn_direction = 0;
    player->walkdirection = 0;
    player->rotationAngle = M_PI / 2;
    player->movespeed = 4.0;
    player->rotationspeed = (M_PI / 20);
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
    mlx_hook(win, 3, 0 , &update_player2, player);
    mlx_loop_hook(mlx, &update_map, player);
    mlx_loop(mlx);
}