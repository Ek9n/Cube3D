/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision_check_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 08:54:54 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/24 12:52:59 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	in_border(t_data *data)
{
	if (data->player->y > 0 && data->player->x > 0
		&& data->player->x < data->map->row_max * IMG_SIZE - IMG_SIZE
		&& data->player->y < data->map->col_max * IMG_SIZE - IMG_SIZE)
		return (1);
	return (0);
}

int	calc_mod(int num)
{
	num %= IMG_SIZE;
	if (num >= (IMG_SIZE / 2))
		num = (num - 63) * -1;
	return (num);
}

int	check_mid_wall(t_map *map, int corner1[2], int corner2[2], int mod[2])
{
	if (mod[0] > mod[1])
	{
		if (map->grid[corner1[0] / IMG_SIZE][corner2[1] / IMG_SIZE] == 1)
			return (1);
	}
	else
	{
		if (map->grid[corner2[0] / IMG_SIZE][corner1[1] / IMG_SIZE] == 1)
			return (1);
	}
	return (0);
}

int	calc_coll_angle(t_data *data, float *angle, int side, int dir)
{
	float	mod;

	mod = ((int)(*angle * 1000) % (int)(0.5 * PI * 1000));
	mod /= 1000;
	if (side == XK_Right)
		*angle += PI - (2 * mod);
	else
		*angle -= PI - (2 * mod);
	adjust_angle(angle);
	if (!data->player->wall_hit)
	{
		data->player->angle = *angle;
		data->rot[side] = data->rot[dir];
	}
	data->player->wall_hit = 1;
	data->player->dead = 1;
	return (1);
}
