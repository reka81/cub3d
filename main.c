#include "cub3d.h"



void put_pixel_to_buffer(char *buffer, int x, int y, int color, int size_line, int bits_per_pixel) {
    if (x < 0 || x >= 64 * 15 || y < 0 || y >= 64 * 10) return;

    // Calculate the position of the pixel in the buffer
    int pixel = (y * size_line) + (x * (bits_per_pixel / 8));

    // Write color to the pixel position in the buffer
    *(unsigned int *)(buffer + pixel) = color;
}

int main()
{
    void *mlx;
    void *win;
    t_player *player;
    int bits_per_pixel;
    int size_line;
    int endian;
    // t_texture *texture;

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
    // texture = malloc(sizeof(t_texture));
    player = malloc(sizeof(t_player));
    mlx = mlx_init();
    win = mlx_new_window(mlx, 64 * 15, 64 * 10, "window");
    void *img = mlx_new_image(mlx, 64 * 15, 64 * 10);
    char *buffer = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    // texture->img = mlx_xpm_file_to_image(mlx, "wall_texture.xpm", texture->width, texture->height);
    // texture->data = mlx_get_data_addr(texture->img, texture->bpp, texture->size_line, texture->endian);
    player_init(player, staticArray, mlx, win);
    draw_image(staticArray, mlx, win,img, buffer, size_line, bits_per_pixel);
    player->buffer = buffer;
    player->size_line = size_line;
    player->img = img;
    player->bits_per_pixel = bits_per_pixel;
    draw_player(player, win, mlx);
    mlx_hook(win, 2, 0, &update_player, player);
    mlx_hook(win, 3, 0 , &update_player2, player);
    mlx_loop_hook(mlx, &update_map, player);
    mlx_clear_window(player->mlx, player->win);
    mlx_loop(mlx);
}