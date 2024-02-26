/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:12:36 by yubi42            #+#    #+#             */
/*   Updated: 2024/02/26 16:48:16 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../lib/libft/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
#include <string.h>
# include <errno.h>
# include <unistd.h>
# include <limits.h>

#define TRUE 1
#define FALSE 0

typedef struct s_read
{
    int fd;
    char buf;
    ssize_t bytes;
    char *str;
    int i;
    int return_value;
}       t_read;

typedef struct s_cub
{
    char* no_path;
    char* so_path;
    char* we_path;
    char* ea_path;
    void* no_addr;
    void* so_addr;
    void* we_addr;
    void* ea_addr;
    int f[3];
    int c[3];
    char *map_str;
}		t_cub;

typedef struct s_cub_ok
{
    int no;
    int so;
    int we;
    int ea;
    int f;
    int c;
}       t_cub_ok;

typedef struct s_map
{
    int **grid;
	int	row_max;
	int	col_max;
    int i;
    int j;
}		t_map;

typedef struct s_data
{
    char err[50];
    t_map *map;
}       t_data;


// ================= SETUP ==================

// err.c

int	malloc_err(void *ptr, int *return_value, char (*err)[50]);

// ================= SETUP ==================

// file_check.c

int		setup_found(t_cub_ok setup_vars);
void	setup_vars_check(t_cub *cub, t_read *reading, t_cub_ok *setup_vars,
			char (*err)[50]);
void	setup_map_str(t_cub *cub, t_read *reading, char (*err)[50]);

// file_line_check.c

int		check_filepath(char **cub, int *setup_var, t_read *reading,
			char (*err)[50]);
int		is_rgb_num(char *str);
int		check_rgb(int (*cub)[3], int *setup_var, t_read *reading,
			char (*err)[50]);
int		line_valid(t_read *reading, t_cub *cub, t_cub_ok *setup_vars,
			char (*err)[50]);

// free_structs.c

void	free_str(char **str);
void	free_ptr(void **ptr);
void	free_cub(t_cub *cub);
void	free_grid(int ***grid, int max_row);
void	free_map(t_map *map);

// init_structs.c

void	init_setup_vars(t_cub_ok *setup_vars);
void	init_reading(t_read *reading);
void	init_cub(t_cub *cub);
void	init_map(t_map *map);
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
int		fill_grid(char *str, t_map *map, char (*err)[50]);

// validators.c

int	map_validator(t_data *data, t_cub cub, char (*err)[50]);
int	file_validator(char *file, t_cub *cub, char (*err)[50]);
int	input_validator(int ac, char **av, char (*err)[50]);


#endif