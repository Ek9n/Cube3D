/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:00:07 by yubi42            #+#    #+#             */
/*   Updated: 2024/06/02 00:22:38 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	north_wall(t_data *data, int x, int y)
{
	if (data->map->grid[(x / IMG_SIZE) - 1][y / IMG_SIZE] == 1)
	{
		data->ray.img = data->texture->no;
		data->ray.img_col = y % IMG_SIZE;
		return (1);
	}
	return (0);
}

int	south_wall(t_data *data, int x, int y)
{
	if (data->map->grid[x / IMG_SIZE][y / IMG_SIZE] == 1)
	{
		data->ray.img = data->texture->so;
		data->ray.img_col = IMG_SIZE - (y % IMG_SIZE) - 1;
		return (1);
	}
	return (0);
}

int	east_wall(t_data *data, int x, int y)
{
	if (data->map->grid[x / IMG_SIZE][y / IMG_SIZE] == 1)
	{
		data->ray.img = data->texture->ea;
		data->ray.img_col = x % IMG_SIZE;
		return (1);
	}
	return (0);
}

int	west_wall(t_data *data, int x, int y)
{
	if (data->map->grid[x / IMG_SIZE][(y / IMG_SIZE) - 1] == 1)
	{
		data->ray.img = data->texture->we;
		data->ray.img_col = IMG_SIZE - (x % IMG_SIZE) - 1;
		return (1);
	}
	return (0);
}

int	wall_found(t_data *data, double x, double y)
{
	adjust_x_y(data, &x, &y);
	data->ray.ray_len = distance(data->ray.x, data->ray.y, x, y);
	if ((int)x % IMG_SIZE == 0)
	{
		if (north_wall(data, x, y))
			return (1);
		if (south_wall(data, x, y))
			return (1);
	}
	if ((int)y % IMG_SIZE == 0)
	{
		if (east_wall(data, x, y))
			return (1);
		if (west_wall(data, x, y))
			return (1);
	}
	return (0);
}

int	north_wall2(t_data *data, int x, int y)
{
	if (data->map->grid[(x / IMG_SIZE) - 1][y / IMG_SIZE] == 1)
	{
		data->ray2.img = data->texture->no;
		data->ray2.img_col = y % IMG_SIZE;
		return (1);
	}
	return (0);
}

int	south_wall2(t_data *data, int x, int y)
{
	if (data->map->grid[x / IMG_SIZE][y / IMG_SIZE] == 1)
	{
		data->ray2.img = data->texture->so;
		data->ray2.img_col = IMG_SIZE - (y % IMG_SIZE) - 1;
		return (1);
	}
	return (0);
}

int	east_wall2(t_data *data, int x, int y)
{
	if (data->map->grid[x / IMG_SIZE][y / IMG_SIZE] == 1)
	{
		data->ray2.img = data->texture->ea;
		data->ray2.img_col = x % IMG_SIZE;
		return (1);
	}
	return (0);
}

int	west_wall2(t_data *data, int x, int y)
{
	if (data->map->grid[x / IMG_SIZE][(y / IMG_SIZE) - 1] == 1)
	{
		data->ray2.img = data->texture->we;
		data->ray2.img_col = IMG_SIZE - (x % IMG_SIZE) - 1;
		return (1);
	}
	return (0);
}

int	wall_found2(t_data *data, double x, double y)
{
	adjust_x_y(data, &x, &y);
	data->ray2.ray_len = distance(data->ray2.x, data->ray2.y, x, y);
	if ((int)x % IMG_SIZE == 0)
	{
		if (north_wall2(data, x, y))
			return (1);
		if (south_wall2(data, x, y))
			return (1);
	}
	if ((int)y % IMG_SIZE == 0)
	{
		if (east_wall2(data, x, y))
			return (1);
		if (west_wall2(data, x, y))
			return (1);
	}
	return (0);
}
