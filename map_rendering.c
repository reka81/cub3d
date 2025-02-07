#include "cub3d.h"

void draw_image(char staticArray[10][17], void *mlx, void *win, void *img, char *buffer, int size_line, int bits_per_pixel) {
    int i = 0, j = 0;

    while (i < 10) {
        j = 0;
        while (staticArray[i][j] != '\n') {
            int color;
            int y = 0;

            if (staticArray[i][j] == '1')
                color = 0xFF0000;
            if (staticArray[i][j] == '0')
                color = 0x000000;

            int x;
            while (y < 64) {
                x = 0;
                while (x < 64) {
                    put_pixel_to_buffer(buffer, j * 64 + x, i * 64 + y, color, size_line, bits_per_pixel);
                    x++;
                }
                put_pixel_to_buffer(buffer, j * 64 + x - 1, i * 64 + y, 0xFFFFFF, size_line, bits_per_pixel);
                y++;
            }
            x = 0;
            while (x < 64) {
                put_pixel_to_buffer(buffer, j * 64 + x, i * 64 + y - 1, 0xFFFFFF, size_line, bits_per_pixel);
                x++;
            }
            j++;
        }
        i++;
    }

    // Update the entire image **only once** after drawing everything
    mlx_put_image_to_window(mlx, win, img, 0, 0);
}
