/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:46:24 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/02 18:16:36 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_texture(t_texture *texture)
{
	texture->minimap = NULL;
	texture->no_path = NULL;
	texture->so_path = NULL;
	texture->we_path = NULL;
	texture->ea_path = NULL;
	texture->base_img = NULL;
	texture->img1 = NULL;
	texture->img2 = NULL;
	texture->black = NULL;
	texture->transparent = NULL;
	texture->steeringwheel = NULL;
	texture->steeringwheel2 = NULL;
	texture->carframe = NULL;
	texture->carframe2 = NULL;
	texture->num0 = NULL;
	texture->num1 = NULL;
	texture->num2 = NULL;
	texture->num3 = NULL;
	texture->num4 = NULL;
	texture->num5 = NULL;
	texture->num6 = NULL;
	texture->num7 = NULL;
	texture->num8 = NULL;
	texture->num9 = NULL;
	texture->slash = NULL;
	texture->kmh = NULL;
	texture->game_over = NULL;
	texture->goal = NULL;
	texture->no = NULL;
	texture->so = NULL;
	texture->ea = NULL;
	texture->we = NULL;
	texture->f[0] = -1;
	texture->f[1] = -1;
	texture->f[2] = -1;
	texture->c[0] = -1;
	texture->c[1] = -1;
	texture->c[2] = -1;
	texture->map_str = NULL;
}

void	init_map(t_map *map)
{
	map->grid = NULL;
	map->col_max = 0;
	map->row_max = 0;
	map->i = 0;
	map->j = 0;
	map->player = 0;
}

void	init_player(t_player *player)
{
	player->x = -1;
	player->y = -1;
	player->angle = -1;
	player->speed[0] = 0;
	player->speed[1] = 0;
	player->speed[2] = 0;
	player->rotation = 0;
	player->rev_speed = 17;
	player->dead = 0;
	player->wall_hit = 0;
}

void	init_array(int array[NUM_KEYS], int num, int num2)
{
	int	i;

	i = 0;
	while (i < NUM_KEYS)
		array[i++] = num;
	array[XK_Up] = num2;
	array[XK_Down] = num2;
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
    data->width = 1920;
    data->height = 1080;
	data->restart = false;
	data->err[0] = '\0';
	data->round = -1;
	data->round_touch = 0;
	data->map = NULL;
	data->texture = NULL;
	data->player = NULL;
	data->player = malloc(sizeof(t_player));
	data->map = malloc(sizeof(t_map));
	data->texture = malloc(sizeof(t_texture));
	init_array(data->keys, 0, 0);
	init_array(data->rot, ROT_MIN, MOV_MIN);
	init_player(data->player);
	init_map(data->map);
	init_texture(data->texture);
}
