/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:03:24 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/24 12:52:59 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

float	distance(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	adjust_angle(float *angle)
{
	if (*angle >= 2 * PI)
		*angle -= 2 * PI;
	if (*angle < 0)
		*angle += 2 * PI;
}

void	adjust_x_y(t_data *data, float *x, float *y)
{
	if (*x - (int)*x > 0 && (!((int)*x % IMG_SIZE == IMG_SIZE - 1)))
		++(*x);
	if (*y - (int)*y > 0 && !((int)*y % IMG_SIZE == IMG_SIZE - 1))
		++(*y);
	if (*x < IMG_SIZE)
		*x = IMG_SIZE;
	if (*y < IMG_SIZE)
		*y = IMG_SIZE;
	if (*x >= data->map->row_max * IMG_SIZE - 1)
		*x = data->map->row_max * IMG_SIZE - 1;
	if (*y >= data->map->col_max * IMG_SIZE - 1)
		*y = data->map->col_max * IMG_SIZE - 1;
}
