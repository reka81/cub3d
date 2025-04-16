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
char *ft_strcpy(char *dest, const char *src) {
    int i = 0;

    while (src[i]) {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
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
int get_num_rows(char **array) {
    int num_rows = 0;

    while (array[num_rows] != NULL) {
        num_rows++;
    }

    return num_rows;
}
int get_longest_row(char **map) {
    int i = 0;
    int max_len = 0;
    while (map[i] != NULL) {
        int len = ft_strlen(map[i]);
        if (len > max_len)
            max_len = len;
        i++;
    }
    return max_len;
}
char **pad_map(char **map, int num_rows, int longest_row, char pad_char) {
    int i;

    // Allocate one extra row for the NULL terminator
    char **padded_map = malloc(sizeof(char *) * (num_rows + 1));
    if (!padded_map) return NULL;

    for (i = 0; i < num_rows; i++) {
        int len = ft_strlen(map[i]);
        padded_map[i] = malloc(longest_row + 1); // +1 for null terminator
        if (!padded_map[i]) return NULL;

        // Copy original content
        ft_strcpy(padded_map[i], map[i]);

        // Pad with pad_char if needed
        for (int j = len; j < longest_row; j++) {
            padded_map[i][j] = pad_char;
        }
        padded_map[i][longest_row] = '\0'; // Null terminate the string
    }

    padded_map[num_rows] = NULL; // Null terminate the array of strings
    return padded_map;
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
    // t_strings *strings = retrieving(ac, av);
    // char **map = strings->map;
    // // printf("%d--%d\n",player->longest_row, player->get_num_rows);
    // map = pad_map(strings->map,player->get_num_rows, player->longest_row, '1');
    // player->longest_row = get_longest_row(strings->map);
    // player->get_num_rows = get_num_rows(strings->map);
        // player->longest_row = get_longest_row(strings->map);
    // player->get_num_rows = get_num_rows(strings->map);
           player->longest_row = 30;
    player->get_num_rows = 15;
    setting_imgs_and_data(texture, mlx, "wall_texture.xpm");
    setting_imgs_and_data(texture2, mlx, "tswiraaaa.xpm");
    setting_imgs_and_data(texture3, mlx, "east_walls.xpm");
    setting_imgs_and_data(texture4, mlx, "west_wall.xpm");
    player->texture = texture;
    void *img = mlx_new_image(mlx, 64 * 15 , 64 * 10);
    char *buffer = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
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
