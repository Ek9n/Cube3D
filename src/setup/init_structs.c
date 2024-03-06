/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:46:24 by yubi42            #+#    #+#             */
/*   Updated: 2024/03/06 14:15:56 by jborner          ###   ########.fr       */
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

void	init_texture(t_texture *cub)
{
	cub->no_path = NULL;
	cub->so_path = NULL;
	cub->we_path = NULL;
	cub->ea_path = NULL;
	cub->no_addr = NULL;
	cub->so_addr = NULL;
	cub->we_addr = NULL;
	cub->ea_addr = NULL;
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
}


void	init_data(t_data *data)
{
	data->err[0] = '\0';
	data->map = NULL;
	data->texture = NULL;
	data->player = NULL;
	data->map = malloc (sizeof(t_map));
	data->texture = malloc (sizeof(t_texture));
	data->player = malloc (sizeof(t_player));
	init_player(data->player);
	init_map(data->map);
	init_texture(data->texture);
}
