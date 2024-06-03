CC      = cc
CFLAGS  = -Wall -Werror -Wextra
NAME    = cub3D

LIBFT   = lib/libft/libft.a
MLX		= lib/.mlx_linux/libmlx.a

SRC_PATH = src/
OBJ_PATH = .obj/
SUBOBJ_PATH	=	.obj/close \
				.obj/control \
				.obj/execute \
				.obj/minimap \
				.obj/mlx \
				.obj/rays \
				.obj/render_utils \
				.obj/setup \
				.obj/sound \
				.obj/data \

SRC	=	main.c \
		close/err.c \
		close/free_structs.c \
		close/free_utils.c \
		control/collision_check.c \
		control/collision_check_utils.c \
		control/key_action.c \
		control/keypress.c \
		execute/render_game.c \
		execute/run_game.c \
		execute/put_score_utils_1.c \
		execute/put_score_utils_2.c \
		execute/put_str_utils.c \
		minimap/create_minimap.c \
		mlx/mlx_init.c \
		rays/cast_rays.c \
		rays/cast_rays_back.c \
		rays/init_ray_checker.c \
		rays/init_ray_checker_back.c \
		rays/ray_checker_utils.c \
		rays/wall_detection.c \
		rays/wall_detection_back.c \
		render_utils/draw_pixel.c \
		render_utils/draw_pixel2.c \
		render_utils/fps.c \
		render_utils/render_utils.c \
		render_utils/resize_img.c \
		render_utils/rotate_utils.c \
		setup/file_check.c \
		setup/file_line_check.c \
		setup/generate_goal.c \
		setup/init_data_struct.c \
		setup/init_other_structs.c \
		setup/map_grid_check.c \
		setup/map_grid_create_n_fill.c \
		setup/validators.c \
		sound/miniaudio.c \
		sound/sound.c \
		data/load_and_save.c \

SRCS    = $(addprefix $(SRC_PATH), $(SRC))
OBJ     = $(SRC:.c=.o)
OBJS    = $(addprefix $(OBJ_PATH), $(OBJ))
INCS    = -I lib/.mlx_linux -Iinc
LDFLAGS = -L lib/libft -lft

all: $(NAME)

m: all
	./cub3D maps/race1.cub

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