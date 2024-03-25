/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:12:36 by yubi42            #+#    #+#             */
/*   Updated: 2024/03/25 13:53:05 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../lib/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <math.h>
# include <mlx.h>
# include <mlx_int.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define TRUE 1
# define FALSE 0
# define PI 3.1415926535
# define IMG_SIZE 64

# define TRANS 0x000000
# define GREEN 0xFF00
# define PURPLE 0xFF00FF
# define YELLOW 0xFFFF00
# define BLACK 0x000001
# define RED 0xFF0000
# define LIME 0x00FF00
# define BLUE 0x0000FF
# define MOVSPEED 1
# define NUM_KEYS 65536
# define ANIM_DELAY 5
#define ROT_MIN 10

typedef struct s_read
{
	int			fd;
	char		buf;
	ssize_t		bytes;
	char		*str;
	int			i;
	int			return_value;
}				t_read;

typedef struct s_image
{
	void *img_ptr; // Zeiger auf das Bild in der Grafikbibliothek
	char *addr;    // Zeiger auf den Anfang des Bildspeichers
	int bpp;       // Bits pro Pixel
	int endian;    // Endianness (1 für big endian, 0 für little endian)
	int			bytes_per_line;
	int			width;
	int			height;
	int			x;
	int			y;
	int			z;
}				t_image;

typedef struct s_minimap
{
	t_image		*base;
	t_image		*resize;
	t_image		*small;
	int			resize_value;
	t_image		*wall;
	t_image		*ground;
	t_image		*player;
	t_image		*player_rot;
	t_image		*exit;

}				t_minimap;

typedef struct s_texture
{
	t_minimap	*minimap;
	t_image		*base_img;
	t_image		*img1;
	t_image		*img2;
	t_image		*no;
	t_image		*so;
	t_image		*ea;
	t_image		*we;

	char		*img_map_ground;
	char		*map_ground;

	char		*no_path;
	char		*so_path;
	char		*we_path;
	char		*ea_path;
	int			f[3];
	int			c[3];
	char		*map_str;
}				t_texture;

typedef struct s_texture_ok
{
	int			no;
	int			so;
	int			we;
	int			ea;
	int			f;
	int			c;
}				t_texture_ok;

typedef struct s_map
{
	int			**grid;
	int			row_max;
	int			col_max;
	int			i;
	int			j;
}				t_map;

typedef struct s_player
{
	float		x;
	float		y;
	float		dx;
	float		dy;
	float		x_sin;
	float		y_cos;
	float		angle;
	float		speed[3];
}				t_player;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	int			width;
	int			height;
	int			keys[NUM_KEYS];
	int			delay[NUM_KEYS];
	int			rot[NUM_KEYS];
	int			minimap_width;
	int			minimap_height;
	char		err[50];
	t_texture	*texture;
	t_map		*map;
	t_player	*player;
}				t_data;

// ================= CLOSE ==================

// err.c
int				malloc_err(void *ptr, int *return_value, char (*err)[50]);
void			close_game(t_data *data, char *msg);

// free_structs.c
void			free_str(char **str);
void			free_ptr(void **ptr);
void			free_img(t_image *img, void *mlx);
void			free_minimap(t_minimap *minimap, t_data *data);
void			free_cub(t_texture *cub, t_data *data);
void			free_grid(int ***grid, int max_row);
void			free_map(t_map *map);
void			free_data(t_data *data);

// ================= CONTROL ==================

// keypress.c

void			move_player(t_data *data, int sign, int num);
void			rotate_player(t_data *data, int sign, int num);
void			handle_keys(t_data *data);
int				handle_keypress(int keysym, t_data *data);
int				handle_keyrelease(int keysym, t_data *data);

// ============== EXECUTE =============

// render_game.c
void			render_minimap(t_data *data, t_minimap *minimap);
void			render_background(t_data *data, t_image *bg);
int				render(t_data *data);

// run_game.c
void			run_game(t_data *data);

// ================= MLX_SETUP ==================

// create_minimap.c
void			create_minimap_texture(t_minimap *minimap, t_data *data);
void			copy_to_small(int player_row, int player_col, t_image *full,
					t_image *part);
void			create_minimap(t_data *data);

// mlx_init.c
void			init_img(t_image *img);
t_image			*create_img(t_data *data, char *path, int w, int h);
void			mlx_init_game(t_data *data);

// ============== RENDER UTILS ==============

// put_pixel.c
void			img_pix_put(t_image *img, int x, int y, int color);
void			put_pixel_img(t_image *img, int x, int y, int color);
unsigned int	get_pixel_img(t_image *img, int x, int y);
void			put_img_to_img(t_image *dst, t_image *src, int x, int y);

// render_utils.c
void			fill_img_color(t_image *img, int color);
void			create_frame(t_image *img, int size, int color);
unsigned long	rgb_to_hex(int rgb[3]);

// resize_img.c
void			scale_img(t_image **old, t_image **new, int w, int h);
t_image			*resize_img(t_data *data, t_image **old, int w, int h);
void			rotate_img(t_data *data, t_image **old, t_image **new);

// ================= SETUP ==================

// file_check.c
int				setup_found(t_texture_ok setup_vars);
void			setup_vars_check(t_texture *cub, t_read *reading,
					t_texture_ok *setup_vars, char (*err)[50]);
void			setup_map_str(t_texture *cub, t_read *reading, char (*err)[50]);

// file_line_check.c
int				check_filepath(char **cub, int *setup_var, t_read *reading,
					char (*err)[50]);
int				is_rgb_num(char *str);
int				check_rgb(int (*cub)[3], int *setup_var, t_read *reading,
					char (*err)[50]);
int				line_valid(t_read *reading, t_texture *cub,
					t_texture_ok *setup_vars, char (*err)[50]);

// init_structs.c

void			init_setup_vars(t_texture_ok *setup_vars);
void			init_reading(t_read *reading);
void			init_minimap(t_minimap *minimap);
void			init_texture(t_texture *cub);
void			init_map(t_map *map);
void			init_player(t_player *player);
void			init_array(int array[NUM_KEYS], int num, int num2);
void			init_data(t_data *data);

// map_grid_check.c
void			check_edge(t_map *map, int *return_value, char (*err)[50]);
void			check_mid(t_map *map, int *return_value, int *player_count,
					char (*err)[50]);
int				check_grid(t_map *map, char (*err)[50]);
void			print_grid(t_map *map);

// map_grid_create_n_fill.c
void			count_map_row_col(char *str, int *max_col, int *max_row);
void			create_grid(t_map *map);
void			newline_grid(t_map *map);
int				fill_grid(char *str, t_map *map, t_player *player,
					char (*err)[50]);

// validators.c
int				map_validator(t_data *data, t_texture cub, char (*err)[50]);
int				file_validator(char *file, t_texture *cub, char (*err)[50]);
int				input_validator(int ac, char **av, char (*err)[50]);

#endif
