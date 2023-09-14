NAME = cub3D

FLAGS = -fsanitize=address -g #-Ofast -O3

CC = cc

mlx_lib = MLX42/libmlx42.a

DEPENDENCIES = -framework Cocoa -framework OpenGL -framework IOKit

glfw = $(shell brew --prefix glfw)

GNL = $(addprefix gnl/, get_next_line.c get_next_line_utils.c)
TOOLS = $(addprefix tools/, ft_split.c ft_strjoin.c ft_strncmp.c ft_strlen.c ft_strchr.c ft_strdup.c ft_substr.c ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_itoa.c ft_atoi.c)
PARS = $(addprefix parsing/, get_elems.c  init_info.c ft_err.c map.c)
RAY_CASTING = $(addprefix ray_casting/, ray_casting.c cast_horizontal_lines.c cast_vertical_lines.c)
HOOK = $(addprefix key_hook/, move_and_rotate.c)
PLOT = $(addprefix plot/, map_and_player.c plotting_tools.c)
TEXTURE = $(addprefix put_textures/, textures.c)

SRS = cub3d.c $(PARS) $(TOOLS) ${GNL} ${RAY_CASTING} ${HOOK} ${PLOT} ${TEXTURE}
OBJS = $(SRS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) Makefile includes/cub3d.h
		$(CC) $(FLAGS) -o $(NAME) $(SRS) $(DEPENDENCIES) -lglfw -L"$(glfw)/lib" $(mlx_lib)

clean:
	rm -f $(OBJS)

run: $(NAME)
	./$(NAME) map.cub
fclean: clean
	rm -f $(NAME)

re: fclean all

