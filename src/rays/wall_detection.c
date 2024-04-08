/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_detection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:00:07 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/08 14:36:24 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	wall_found(t_data *data, float cur_x, float cur_y)
{
	int x;
	int y;

	x = cur_x;
	y = cur_y;
	if (cur_x - x >= 0.9)
		++x;
	if (cur_y - y >= 0.9)
		++y;
	// if (cur_x - x >= 0.1)
	// 	--x;
	// if (cur_y - y >= 0.1)
	// 	--y;

	if (x < 0 + IMG_SIZE|| x >= data->map->row_max * IMG_SIZE -( IMG_SIZE -1) || y < 0 + IMG_SIZE|| y >= data->map->col_max * IMG_SIZE -( IMG_SIZE -1))
	{
		if(data->map->grid[(x / IMG_SIZE) - 1][(y / IMG_SIZE) - 1] == 1 || data->map->grid[(x / IMG_SIZE)][(y / IMG_SIZE)] == 1 || data->map->grid[(x / IMG_SIZE) - 1][(y / IMG_SIZE)] == 1 || data->map->grid[(x / IMG_SIZE)][(y / IMG_SIZE) - 1] == 1)
		{	
			data->ray.img_dir = 'B';
			data->ray.img_col = 1;
			printf("BAEH.. cur_x: %f cur_y %f \n", cur_x, cur_y);
			return (1);
		}
	}
	if (x % IMG_SIZE == 0 && y % IMG_SIZE == 0)
	{
		if(data->map->grid[(x / IMG_SIZE) - 1][(y / IMG_SIZE) - 1] == 1 || data->map->grid[(x / IMG_SIZE)][(y / IMG_SIZE)] == 1 || data->map->grid[(x / IMG_SIZE) - 1][(y / IMG_SIZE)] == 1 || data->map->grid[(x / IMG_SIZE)][(y / IMG_SIZE) - 1] == 1)
		{
			// printf("WALL FOUND\n");
			data->ray.img_dir = 'B';
			data->ray.img_col = y % IMG_SIZE;
			return (1);
		}
	}
	if (x % IMG_SIZE == 0)
	{
		if (data->map->grid[(x / IMG_SIZE) - 1][y / IMG_SIZE] == 1)
		{
			// printf("WALL FOUND\n");
			data->ray.img_dir = 'N';
			data->ray.img_col = y % IMG_SIZE;
			return (1);
		}
		if(data->map->grid[x / IMG_SIZE][y / IMG_SIZE] == 1)
		{
			// printf("WALL FOUND\n");
			data->ray.img_dir = 'S';
			data->ray.img_col = IMG_SIZE - (y % IMG_SIZE) - 1;
			return (1);
		}

	}
	if(y % IMG_SIZE == 0)
	{
		if (data->map->grid[x / IMG_SIZE][(y / IMG_SIZE) - 1] == 1)
		{
			// printf("WALL FOUND\n");
			data->ray.img_dir = 'W';
			data->ray.img_col = IMG_SIZE - (x % IMG_SIZE) - 1;
			return (1);
		}
		if (data->map->grid[x / IMG_SIZE][y / IMG_SIZE] == 1)
		{
			// printf("WALL FOUND\n");
			data->ray.img_dir = 'E';
			data->ray.img_col = x % IMG_SIZE;
			return (1);
		}

	}
	return (0);
}
