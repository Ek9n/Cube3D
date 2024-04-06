CC      = cc
CFLAGS  = -g -Wall -Werror -Wextra
NAME    = cub3d

LIBFT   = lib/libft/libft.a
MLX		= lib/.mlx_linux/libmlx.a

SRC_PATH = src/
OBJ_PATH = .obj/
SUBOBJ_PATH = .obj/close \
				.obj/control \
				.obj/execute \
				.obj/minimap \
				.obj/mlx \
				.obj/rays \
				.obj/render_utils \
				.obj/setup \
				
				

SRC		=	main.c \
			close/err.c \
			close/free_structs.c \
			control/keypress.c \
			execute/delay.c \
			execute/render_game.c \
			execute/run_game.c \
			minimap/create_minimap.c \
			mlx/mlx_init.c \
			rays/cast_rays.c \
			rays/init_ray_checker.c \
			rays/ray_checker_utils.c \
			rays/wall_detection.c \
			render_utils/draw_pixel.c \
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