/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:12:36 by yubi42            #+#    #+#             */
/*   Updated: 2024/03/14 13:49:25 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../lib/libft/libft.h"
# include <mlx.h>
# include <mlx_int.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <limits.h>

#define TRUE 1
#define FALSE 0
#define IMG_SIZE 64

#define TRANS 0x000000
#define GREEN 0xFF00
#define PURPLE 0xFF00FF
#define YELLOW 0xFFFF00
#define BLACK 0x000001
#define RED 0xFF0000
#define LIME 0x00FF00
#define BLUE 0x0000FF

typedef struct s_read
{
    int fd;
    char buf;
    ssize_t bytes;
    char *str;
    int i;
    int return_value;
}       t_read;

typedef struct  s_img
{
    void    *img_ptr;   // Zeiger auf das Bild in der Grafikbibliothek
    char    *addr;      // Zeiger auf den Anfang des Bildspeichers
    int     bpp;        // Bits pro Pixel
    int     endian;     // Endianness (1 für big endian, 0 für little endian)
    int     bytes_per_line;
    int     width;
    int     height;
    int     x;
    int     y;
    int     z;
} t_img;

typedef struct s_texture
{
    t_img *base_img;
    t_img *map_img;
    t_img *floor;
    t_img *wall;
    t_img *exit;
    t_img *player;
    t_img *img1;
    t_img *img2;
    t_img *no;
    t_img *so;
    t_img *ea;
    t_img *we;

    char* img_map_ground;
    char* map_ground;

    char* no_path;
    char* so_path;
    char* we_path;
    char* ea_path;
    int f[3];
    int c[3];
    char *map_str;
}		t_texture;

typedef struct s_texture_ok
{
    int no;
    int so;
    int we;
    int ea;
    int f;
    int c;
}       t_texture_ok;

typedef struct s_map
{
    int **grid;
	int	row_max;
	int	col_max;
    int i;
    int j;
}		t_map;

typedef struct s_player
{
    float x;
    float y;
    float angle;
}       t_player;

typedef struct s_data
{
    void    *mlx;
    void    *mlx_win;
    int     width;
    int     height;
    char err[50];
    t_texture *texture;
    t_map *map;
    t_player *player;
}       t_data;



// ================= SETUP ==================

// file_check.c

int		setup_found(t_texture_ok setup_vars);
void	setup_vars_check(t_texture *cub, t_read *reading, t_texture_ok *setup_vars,
			char (*err)[50]);
void	setup_map_str(t_texture *cub, t_read *reading, char (*err)[50]);



// file_line_check.c

int		check_filepath(char **cub, int *setup_var, t_read *reading,
			char (*err)[50]);
int		is_rgb_num(char *str);
int		check_rgb(int (*cub)[3], int *setup_var, t_read *reading,
			char (*err)[50]);
int		line_valid(t_read *reading, t_texture *cub, t_texture_ok *setup_vars,
			char (*err)[50]);

// free_structs.c

void	free_str(char **str);
void	free_ptr(void **ptr);
void	free_cub(t_texture *cub);
void	free_grid(int ***grid, int max_row);
void	free_map(t_map *map);
void	free_data(t_data *data);

// init_structs.c

void	init_setup_vars(t_texture_ok *setup_vars);
void	init_reading(t_read *reading);
void	init_texture(t_texture *cub);
void	init_map(t_map *map);
void	init_player(t_player *player);
void	init_data(t_data *data);

// map_grid_check.c

void	check_edge(t_map *map, int *return_value, char (*err)[50]);
void	check_mid(t_map *map, int *return_value, int *player_count,
			char (*err)[50]);
int		check_grid(t_map *map, char (*err)[50]);
void	print_grid(t_map *map);

// map_grid_create_n_fill.c

void	count_map_row_col(char *str, int *max_col, int *max_row);
void	create_grid(t_map *map);
void	newline_grid(t_map *map);
int		fill_grid(char *str, t_map *map, t_player *player, char (*err)[50]);

// validators.c

int	map_validator(t_data *data, t_texture cub, char (*err)[50]);
int	file_validator(char *file, t_texture *cub, char (*err)[50]);
int	input_validator(int ac, char **av, char (*err)[50]);

// ================= MLX_SETUP ==================

// mlx_init.c

t_img    *create_img(t_data *data, char *path, int w, int h);
void    mlx_init_game(t_data *data);

// ============== EXECUTE =============

// run_game.c

void    run_game(t_data *data);
void	mlx_init_data(t_data *data);


// ================= CLOSE ==================

// err.c

int     malloc_err(void *ptr, int *return_value, char (*err)[50]);
void	close_game(t_data *data, char *msg);

// ============== JESS =============



// ============== HANNES =============
// ================= CONTROL ==================
// keypress.c
int handle_keypress(int keysym, t_data *data);
// ================= EVENTS ==================
// collision.c


#endif
