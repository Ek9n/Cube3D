/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:00:07 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/18 12:47:32 by yubi42           ###   ########.fr       */
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

int	wall_found(t_data *data, float x, float y)
{
	adjust_x_y(data, &x, &y);
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
