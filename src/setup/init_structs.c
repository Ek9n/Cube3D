/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:46:24 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/15 16:13:38 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_setup_vars(t_texture_ok *setup_vars)
{
	setup_vars->no = FALSE;
	setup_vars->so = FALSE;
	setup_vars->ea = FALSE;
	setup_vars->we = FALSE;
	setup_vars->f = FALSE;
	setup_vars->c = FALSE;
}

void	init_reading(t_read *reading)
{
	reading->return_value = TRUE;
	reading->str = NULL;
	reading->i = 0;
}

void init_minimap(t_minimap *minimap)
{
	minimap->base = NULL;
	minimap->resize = NULL;
	minimap->small = NULL;
	minimap->wall = NULL;
	minimap->ground = NULL;
	minimap->player = NULL;
	minimap->player_rot = NULL;
}

void	init_texture(t_texture *cub)
{
	cub->minimap = NULL;
	cub->no_path = NULL;
	cub->so_path = NULL;
	cub->we_path = NULL;
	cub->ea_path = NULL;
	cub->base_img = NULL;
	cub->img1 = NULL;
	cub->img2 = NULL;
	cub->black = NULL;
	cub->no = NULL;
	cub->so = NULL;
	cub->ea = NULL;
	cub->we = NULL;
	cub->f[0] = -1;
	cub->f[1] = -1;
	cub->f[2] = -1;
	cub->c[0] = -1;
	cub->c[1] = -1;
	cub->c[2] = -1;
	cub->map_str = NULL;
}

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->col_max = 0;
	map->row_max = 0;
	map->i = 0;
	map->j = 0;
}

void	init_player(t_player *player)
{
	player->x = -1;
	player->y = -1;
	player->angle = -1;
	player->speed[0] = 0;
	player->speed[1] = 0;
	player->speed[2] = 0;
	player->dead = 0;
	player->wall_hit = 0;
}

void	init_array(int array[NUM_KEYS], int num, int num2)
{
	int i;

	i = 0;
	while(i < NUM_KEYS)
		array[i++] = num;
	array[XK_Up] = num2;
	array[XK_Down] = num2;
}


void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
    data->width = 1600;
    data->height = 800;
	data->err[0] = '\0';
	data->map = NULL;
	data->texture = NULL;
	data->player = NULL;
	data->player = malloc (sizeof(t_player));
	data->map = malloc (sizeof(t_map));
	data->texture = malloc (sizeof(t_texture));
	init_array(data->keys, 0, 0);
	init_array(data->delay, 0, 0);
	init_array(data->rot, ROT_MIN, MOV_MIN);
	data->rot_dir = 0;
	data->mov_speed = 0;
	init_player(data->player);
	init_map(data->map);
	init_texture(data->texture);
}
