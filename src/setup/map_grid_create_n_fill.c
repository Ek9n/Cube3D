/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid_create_n_fill.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:55:14 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/18 13:08:00 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	count_map_row_col(char *str, int *max_col, int *max_row)
{
	int	i;
	int	col;

	i = 0;
	col = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			if (col > *max_col)
				*max_col = col;
			(*max_row)++;
			col = 0;
		}
		else
			col++;
		i++;
	}
	(*max_row)++;
	if (str[i - 1] == '\n')
		(*max_row)--;
}

void	create_grid(t_map *map)
{
	int	i;

	i = 0;
	map->grid = malloc(sizeof(int *) * map->row_max);
	if (!map->grid)
		return ;
	while (i < map->row_max)
	{
		map->grid[i] = malloc(sizeof(int) * map->col_max);
		if (!map->grid[i])
		{
			free_grid(&map->grid, i);
			break ;
		}
		++i;
	}
}

void	newline_grid(t_map *map)
{
	while (map->i < map->col_max)
		map->grid[map->j][map->i++] = -1;
	map->i = 0;
	++map->j;
}

void	set_player(t_player *player, t_map *map, char c)
{
	map->grid[map->j][map->i] = 2;
	player->x = map->j * IMG_SIZE;
	player->y = map->i * IMG_SIZE;
	if (c == 'N')
		player->angle = 1.5 * PI;
	else if (c == 'E')
		player->angle = 0;
	else if (c == 'S')
		player->angle = 0.5 * PI;
	else if (c == 'W')
		player->angle = 1 * PI;
	player->dx = sin(player->angle) * MOVSPEED;
	player->dy = cos(player->angle) * MOVSPEED;
	player->x_sin = sin(player->angle);
	player->y_cos = cos(player->angle);
	set_corners(player);
	map->i++;
}

int	fill_grid(char *str, t_map *map, t_player *player, char (*err)[50])
{
	int	s_i;

	s_i = -1;
	while (str[++s_i])
	{
		if (str[s_i] == ' ')
			map->grid[map->j][map->i++] = -1;
		else if (str[s_i] == '1')
			map->grid[map->j][map->i++] = 1;
		else if (str[s_i] == '0')
			map->grid[map->j][map->i++] = 0;
		else if (str[s_i] == 'N' || str[s_i] == 'E' || str[s_i] == 'S'
			|| str[s_i] == 'W')
			set_player(player, map, str[s_i]);
		else if (str[s_i] == '\n')
			newline_grid(map);
		else
		{
			ft_strlcpy(*err, "Wrong char", ft_strlen("Wrong char") + 1);
			return (FALSE);
		}
	}
	while (map->i < map->col_max)
		map->grid[map->j][map->i++] = -1;
	return (TRUE);
}
