/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_struct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:46:24 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/27 14:29:35 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

void	init_in_data_structs(t_data *data)
{
	data->map = NULL;
	data->texture = NULL;
	data->player = NULL;
	data->map = malloc(sizeof(t_map));
	data->texture = malloc(sizeof(t_texture));
	data->player = malloc(sizeof(t_player));
}

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->mlx_win = NULL;
	data->width = 1920;
	data->height = 1080;
	data->highscore = 0;
	data->cur_score = 0;
	data->sound_on = false;
	data->start_time.tv_sec = 0;
	data->start_time.tv_usec = 0;
	data->siren = 0;
	data->err[0] = '\0';
	data->round = -1;
	data->round_touch = 0;
	data->end_reached = 0;
	init_in_data_structs(data);
	init_array(data->keys, 0, 0);
	init_array(data->rot, ROT_MIN, MOV_MIN);
	init_player(data->player);
	init_map(data->map);
	init_texture(data->texture);
}
