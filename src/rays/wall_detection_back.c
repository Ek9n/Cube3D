/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detection_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:09:41 by jborner           #+#    #+#             */
/*   Updated: 2024/06/03 14:11:08 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	north_wall_back(t_data *data, int x, int y)
{
	if (data->map->grid[(x / IMG_SIZE) - 1][y / IMG_SIZE] == 1)
	{
		data->ray_back.img = data->texture->no;
		data->ray_back.img_col = y % IMG_SIZE;
		return (1);
	}
	return (0);
}

int	south_wall_back(t_data *data, int x, int y)
{
	if (data->map->grid[x / IMG_SIZE][y / IMG_SIZE] == 1)
	{
		data->ray_back.img = data->texture->so;
		data->ray_back.img_col = IMG_SIZE - (y % IMG_SIZE) - 1;
		return (1);
	}
	return (0);
}

int	east_wall_back(t_data *data, int x, int y)
{
	if (data->map->grid[x / IMG_SIZE][y / IMG_SIZE] == 1)
	{
		data->ray_back.img = data->texture->ea;
		data->ray_back.img_col = x % IMG_SIZE;
		return (1);
	}
	return (0);
}

int	west_wall_back(t_data *data, int x, int y)
{
	if (data->map->grid[x / IMG_SIZE][(y / IMG_SIZE) - 1] == 1)
	{
		data->ray_back.img = data->texture->we;
		data->ray_back.img_col = IMG_SIZE - (x % IMG_SIZE) - 1;
		return (1);
	}
	return (0);
}

int	wall_found_back(t_data *data, double x, double y)
{
	adjust_x_y(data, &x, &y);
	data->ray_back.ray_len = distance(data->ray_back.x, data->ray_back.y, x, y);
	if ((int)x % IMG_SIZE == 0)
	{
		if (north_wall_back(data, x, y))
			return (1);
		if (south_wall_back(data, x, y))
			return (1);
	}
	if ((int)y % IMG_SIZE == 0)
	{
		if (east_wall_back(data, x, y))
			return (1);
		if (west_wall_back(data, x, y))
			return (1);
	}
	return (0);
}
