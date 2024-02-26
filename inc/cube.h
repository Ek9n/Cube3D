/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 12:12:36 by yubi42            #+#    #+#             */
/*   Updated: 2024/02/26 16:20:52 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "hannes.h"
# include "jess.h"
# include "../lib/libft/libft.h"
# include <mlx.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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
    void* no;
    void* so;
    void* we;
    void* ea;
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

typedef struct s_player
{
    int x;
    int y;
    float rot;
}		t_player;

typedef struct s_data
{
    char err[50];
    t_img *img;
    t_player *player;
    t_cub *cub;
    t_map *map;
}       t_data;

typedef struct s_img
{
	void *mlx_img;
	char *addr;


} t_img;

#endif