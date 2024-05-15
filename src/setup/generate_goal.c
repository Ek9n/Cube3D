/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_goal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:04:36 by jborner           #+#    #+#             */
/*   Updated: 2024/05/15 16:11:47 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	opt1_fill_start(t_map *map, int k, int opt)
{
	while ((map->grid[k][map->i] != 1 && map->grid[k][map->i] != -1)
		&& (k < map->row_max && k >= 0) && (map->i < map->col_max
			&& map->i >= 0))
	{
		map->grid[k][map->i] = 2;
		if (opt == 1)
			++k;
		else
			--k;
	}
}

void	opt2_fill_start(t_map *map, int k, int opt)
{
	while ((map->grid[map->j][k] != 1 && map->grid[map->j][k] != -1)
		&& (k < map->col_max && k >= 0) && (map->j < map->row_max
			&& map->j >= 0))
	{
		map->grid[map->j][k] = 2;
		if (opt == 1)
			++k;
		else
			--k;
	}
}

void	choose_fill_start(t_map *map, int c)
{
	map->grid[map->j][map->i] = 0;
	if (c == 2)
	{
		map->j -= 1;
		opt2_fill_start(map, map->i, 1);
		opt2_fill_start(map, map->i, 2);
	}
	else if (c == 3)
	{
		map->i += 1;
		opt1_fill_start(map, map->j, 1);
		opt1_fill_start(map, map->j, 2);
	}
	else if (c == 4)
	{
		map->j += 1;
		opt2_fill_start(map, map->i, 1);
		opt2_fill_start(map, map->i, 2);
	}
	else if (c == 5)
	{
		map->i -= 1;
		opt1_fill_start(map, map->j, 1);
		opt1_fill_start(map, map->j, 2);
	}
}

void	set_start(t_map *map)
{
	while (map->j < map->row_max)
	{
		map->i = -1;
		while (map->i < map->col_max - 1)
		{
			map->i++;
			if (map->grid[map->j][map->i] == 2 || map->grid[map->j][map->i] == 3
				|| map->grid[map->j][map->i] == 4
				|| map->grid[map->j][map->i] == 5)
			{
				choose_fill_start(map, map->grid[map->j][map->i]);
				break ;
			}
		}
		if (map->grid[map->j][map->i] == 2 || map->grid[map->j][map->i] == 3
			|| map->grid[map->j][map->i] == 4 || map->grid[map->j][map->i] == 5)
			break ;
		map->j++;
	}
}
