#include "cub3d.h"

int update_player(int keycode ,t_player *player)
{

    if (keycode == 123 || keycode == 0)
    {
        player->turn_direction = +1;
    }
    if (keycode == 124 || keycode == 2)
    {
        player->turn_direction = -1;
    }
    if (keycode == 126 || keycode == 13)
    {
        player->walkdirection = +1;
    }
    if (keycode == 125 || keycode == 1)
    {
        player->walkdirection = -1;
    }
        return(0);
}
int update_player2(int keycode, t_player *player)
{
    if (keycode == 123 || keycode == 124 || keycode == 0 || keycode == 2)
    {
        player->turn_direction = 0;
    }
    if(keycode == 125 || keycode == 126 || keycode == 13 || keycode == 1)
        player->walkdirection = 0;
    return(0);
}