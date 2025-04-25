NAME = cub3d
CC = cc
FLAGS =  -fsanitize=address -g 
RM = rm -rf

SRCS = main.c player.c raycast.c updating_player.c updating_map.c \
	libft.c pars.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
	get_next_line/ft_strdup.c get_next_line/ft_memcpy.c main_part2.c main_part3.c \
	raycast2.c draw_map3d.c raycast3.c pars1.c pars2.c pars3.c pars4.c pars5.c pars6.c main2.c \
	pars7.c
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