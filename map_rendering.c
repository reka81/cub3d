#include "cub3d.h"

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
            while(y < 13)
            {
                x = 0;
                while (x < 13)
                {
                    mlx_pixel_put(mlx, win, j * 13 + x , i * 13 + y, color);
                    x++;
                }
                mlx_pixel_put(mlx, win, j *13 + x - 1, i*13 + y, 0xFFFFFF);
                y++;
            }
            x = 0;
            while (x < 13)
            {
                mlx_pixel_put(mlx, win, j * 13 + x, i *13 + y - 1, 0xFFFFFF);
                x++;
            }
            j++;
        }
        i++;
    }
}