/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_grid_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:01:10 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/15 16:03:19 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	check_edge(t_map *map, int *return_value, char (*err)[50])
{
	if (!(map->grid[map->j][map->i] == -1 || map->grid[map->j][map->i] == 1))
	{
		ft_strlcpy(*err, "Edge of map has to be walls",
			ft_strlen("Edge of map has to be walls") + 1);
		*return_value = FALSE;
	}
}

void	check_mid(t_map *map, int *return_value, int *player_count,
		char (*err)[50])
{
	if ((map->grid[map->j - 1][map->i] == -1 || map->grid[map->j + 1][map->i] ==
			-1 || map->grid[map->j][map->i - 1] == -1
			|| map->grid[map->j][map->i + 1] == -1)
		&& !(map->grid[map->j][map->i] == -1 || map->grid[map->j][map->i] == 1))
	{
		ft_strlcpy(*err, "Edge of map has to be walls",
			ft_strlen("Edge of map has to be walls") + 1);
		*return_value = FALSE;
	}
	else if ((map->grid[map->j - 1][map->i - 1] == -1 || map->grid[map->j
			+ 1][map->i + 1] == -1 || map->grid[map->j + 1][map->i - 1] == -1
			|| map->grid[map->j - 1][map->i + 1] == -1)
		&& !(map->grid[map->j][map->i] == -1 || map->grid[map->j][map->i] == 1))
	{
		ft_strlcpy(*err, "Map inner corner has to be wall",
			ft_strlen("Map inner corner has to be wall") + 1);
		*return_value = FALSE;
	}
	if (map->grid[map->j][map->i] == 2 || map->grid[map->j][map->i] == 3
		|| map->grid[map->j][map->i] == 4 || map->grid[map->j][map->i] == 5)
		(*player_count)++;
}

int	check_grid(t_map *map, char (*err)[50])
{
	int	player_count;
	int	return_value;

	return_value = TRUE;
	player_count = 0;
	while (map->j < map->row_max)
	{
		map->i = 0;
		while (map->i < map->col_max)
		{
			if (map->j == 0 || map->j == map->row_max - 1 || map->i == 0
				|| map->i == map->col_max - 1)
				check_edge(map, &return_value, err);
			else
				check_mid(map, &return_value, &player_count, err);
			map->i++;
		}
		map->j++;
	}
	if (player_count != 1)
	{
		ft_strlcpy(*err, "Player must be 1", ft_strlen("Player must be 1") + 1);
		return_value = FALSE;
	}
	return (return_value);
}

void	print_grid(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->row_max)
	{
		j = 0;
		while (j < map->col_max)
			j++;
		i++;
	}
}
