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

    char **padded_map = malloc(sizeof(char *) * (num_rows + 1));
    if (!padded_map) return NULL;

    for (i = 0; i < num_rows; i++) {
        
        int len = ft_strlen(map[i]);
        padded_map[i] = malloc(longest_row + 1);
        if (!padded_map[i]) return NULL;

        ft_strcpy(padded_map[i], map[i]);

        for (int j = len; j < longest_row; j++) {
            padded_map[i][j] = pad_char;
        }
        padded_map[i][longest_row] = '\0'; 
    }

    padded_map[num_rows] = NULL; 
    return padded_map;
}
void locate_player(t_player * player, char **map)
{
    int i = 0;
    int j =0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
            if(map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'W' || map[i][j] == 'E')
            {
                player->x = 64 * j;
                player->y = 64 * i;
                if(map[i][j] == 'N')
                     player->rotationAngle = M_PI / 2;
                if(map[i][j] == 'S')
                    player->rotationAngle = 3 * M_PI / 2;
                if(map[i][j] == 'W')
                    player->rotationAngle = M_PI;
                if(map[i][j] == 'E')
                    player->rotationAngle = 2 * M_PI;
                    
                return ;
            }
                j++;
        }
        i++;
    }
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

    textures = malloc (sizeof(t_texture) * 4);
    texture = malloc(sizeof(t_texture));
    texture2 = malloc(sizeof(t_texture));
    texture3 = malloc(sizeof(t_texture));
    texture4 = malloc(sizeof(t_texture));
    mlx = NULL;
    player = malloc(sizeof(t_player));
    mlx = mlx_init();
    win = mlx_new_window(mlx, 64 * 15, 64 * 10, "window");
    t_strings *strings = retrieving(ac, av);

    char **map = strings->map;
    player->longest_row = get_longest_row(strings->map);
    player->get_num_rows = get_num_rows(strings->map);
    map = pad_map(map,player->get_num_rows, player->longest_row, '1');
    locate_player(player, map);
    setting_imgs_and_data(texture, mlx, "wall_texture.xpm");
    setting_imgs_and_data(texture2, mlx, "tswiraaaa.xpm");
    setting_imgs_and_data(texture3, mlx, "east_walls.xpm");
    setting_imgs_and_data(texture4, mlx, "west_wall.xpm");
    player->texture = texture;
    void *img = mlx_new_image(mlx, 64 * 15 , 64 * 10);
    char *buffer = mlx_get_data_addr(img, &bits_per_pixel, &size_line, &endian);
    player_init(player, map, mlx, win);
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
