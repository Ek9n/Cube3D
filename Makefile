CC      = gcc
CFLAGS  = -g -Wall -Werror -Wextra
NAME    = cube3d

LIBFT   = lib/libft/libft.a
MLX		= lib/.mlx_linux/libmlx.a

SRC_PATH = src/
OBJ_PATH = .obj/
SUBOBJ_PATH = .obj/close \
				.obj/control \
				.obj/execute \
				.obj/render_utils \
				.obj/mlx_setup \
				.obj/setup \
				
				

SRC		=	main.c \
			close/err.c \
			close/free_structs.c \
			control/keypress.c \
			execute/render_game.c \
			execute/run_game.c \
			mlx_setup/create_minimap.c \
			mlx_setup/mlx_init.c \
			render_utils/put_pixel.c \
			render_utils/render_utils.c \
			render_utils/resize_img.c \
			setup/file_check.c \
			setup/file_line_check.c \
			setup/init_structs.c \
			setup/map_grid_check.c \
			setup/map_grid_create_n_fill.c \
			setup/validators.c \
			
			

SRCS    = $(addprefix $(SRC_PATH), $(SRC))
OBJ     = $(SRC:.c=.o)
OBJS    = $(addprefix $(OBJ_PATH), $(OBJ))
INCS    = -I lib/.mlx_linux -Iinc
LDFLAGS = -L lib/libft -lft

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH) $(SUBOBJ_PATH)
	$(CC) $(CFLAGS) $(INCS) -O3 -c $< -o $@

$(MLX):
	@if [ ! -d "./lib/.mlx_linux/" ]; then \
		git clone git@github.com:42Paris/minilibx-linux.git ./lib/.mlx_linux/; \
	fi
	@if [ ! -d "./lib/.mlx_linux//build" ]; then \
		cd ./lib/.mlx_linux/ && make; \
	fi

$(LIBFT):
	$(MAKE) -s -C lib/libft all

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -L lib/.mlx_linux -l mlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -rf $(OBJ_PATH)
	$(MAKE) -s -C lib/libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -s -C lib/libft fclean

re: fclean all

.PHONY: all clean fclean re