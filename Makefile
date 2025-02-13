NAME = cub3d
CC = cc
FLAGS =   -fsanitize=address -g
RM = rm -rf

SRCS = main.c map_rendering.c player.c raycast.c updating_player.c updating_map.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -lmlx -framework OpenGL -framework AppKit $(OBJS) -o $(NAME)

%.o:%.c
	$(CC) $(FLAGS) -c $< -o $@
clean :
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re: fclean all