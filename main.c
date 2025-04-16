#include "cub3d.h"
#include "parsing.h"

void put_pixel_to_buffer(char *buffer, int x, int y, int color, int size_line, int bits_per_pixel) {
    if (x < 0 || x >= 64 * 15 || y < 0 || y >= 64 * 10) return;

    int pixel = (y * size_line) + (x * (bits_per_pixel / 8));

    *(unsigned int *)(buffer + pixel) = color;
}

void texture_init(t_texture *texture, t_texture *texture2)
{
    texture->data = NULL;
    texture->img = NULL;
    texture->size_line = 0;
    texture->bpp = 0;
    texture->endian = 0;
    texture2->data = NULL;
    texture2->img = NULL;
    texture2->size_line = 0;
    texture2->bpp = 0;
    texture2->endian = 0;
}

void setting_imgs_and_data(t_texture *texture, void *mlx, char * string)
{
    texture->img = mlx_xpm_file_to_image(mlx, string, &texture->width, &texture->height);
    texture->data = mlx_get_data_addr(texture->img, &texture->bpp, &texture->size_line, &texture->endian);
}
void init_vars_mlx(void *win, void *mlx, t_player *player)
{
    mlx_hook(win, 2, 0, &update_player, player);
    mlx_hook(win, 3, 0 , &update_player2, player);
    mlx_loop_hook(mlx, &update_map, player);
    mlx_clear_window(player->mlx, player->win);
    mlx_loop(mlx);
}
int get_num_rows(double **array) {
    int num_rows = 0;

    while (array[num_rows] != NULL) {
        num_rows++;
    }

    return num_rows;
}
double* get_longest_line(double** array, int rows) {
    int max_length = 0;
    double* longest_row = NULL;

    for (int i = 0; i < rows; i++) {
        int current_length = 0;
        while (array[i][current_length] != '\0') {
            current_length++;
        }

        if (current_length > max_length) {
            max_length = current_length;
            longest_row = array[i];
        }
    }

    return longest_row;
}

int main(int ac, char **av)
{
    void *mlx;
    void *win;
    t_player *player;
    int bits_per_pixel;
    int size_line;
    int endian;
    t_texture **textures;
    t_texture *texture;
    t_texture *texture2;
    t_texture *texture3;
    t_texture *texture4;

char staticArray[15][32] = {
    {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','\n','\0'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','\n','\0'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','\n','\0'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','\n','\0'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','\n','\0'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','\n','\0'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','\n','\0'},
    {'1','0','0','0','0','0','0','C','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','\n','\0'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','\n','\0'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','\n','\0'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','\n','\0'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','\n','\0'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','\n','\0'},
    {'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1','\n','\0'},
    {'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','\n','\0'}
};

    textures = malloc (sizeof(t_texture) * 4);
    texture = malloc(sizeof(t_texture));
    texture2 = malloc(sizeof(t_texture));
    texture3 = malloc(sizeof(t_texture));
    texture4 = malloc(sizeof(t_texture));
    mlx = NULL;
    player = malloc(sizeof(t_player));
    mlx = mlx_init();
    win = mlx_new_window(mlx, 64 * 15, 64 * 10, "window");
    setting_imgs_and_data(texture, mlx, "wall_texture.xpm");
    setting_imgs_and_data(texture2, mlx, "tswiraaaa.xpm");
    setting_imgs_and_data(texture3, mlx, "east_walls.xpm");
    setting_imgs_and_data(texture4, mlx, "west_wall.xpm");
    player->texture = texture;
    void *img = mlx_new_image(mlx, 64 * 15 , 64 * 10);
    char *buffer = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    player->longest_row = 30;
    player->get_num_rows = 15;
    player_init(player, staticArray, mlx, win);
    player->buffer = buffer;
    player->size_line = size_line;
    player->img = img;
    player->bits_per_pixel = bits_per_pixel;
    textures[0] = texture;
    textures[1] = texture2;
    textures[2] = texture3;
    textures[3] = texture4;
    player->textures = textures;
    init_vars_mlx(win, mlx, player);
}
