CC      = gcc
CFLAGS  = -Wall -Werror -Wextra -g
NAME    = cube3d

LIBFT   = lib/libft/libft.a

SRC_PATH = src/
OBJ_PATH = .obj/
SUBOBJ_PATH = .obj/err_handler \
				.obj/setup \

SRC		=	main.c \
			err_handler/err.c \
			setup/file_check.c \
			setup/file_line_check.c \
			setup/free_structs.c \
			setup/init_structs.c \
			setup/map_grid_check.c \
			setup/map_grid_create_n_fill.c \
			setup/validators.c \

SRCS    = $(addprefix $(SRC_PATH), $(SRC))
OBJ     = $(SRC:.c=.o)
OBJS    = $(addprefix $(OBJ_PATH), $(OBJ))
INCS    = -I lib/mlx_linux -Iinc
LDFLAGS = -L lib/libft -lft

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(OBJ_PATH) $(SUBOBJ_PATH)
	$(CC) $(CFLAGS) $(INCS) -O3 -c $< -o $@

$(LIBFT):
	$(MAKE) -s -C lib/libft all

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -L lib/mlx_linux -l mlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -rf $(OBJ_PATH)
	$(MAKE) -s -C lib/libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -s -C lib/libft fclean

re: fclean all

.PHONY: all clean fclean re