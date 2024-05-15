/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_checker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 18:03:24 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/15 15:38:48 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

double	distance(double x1, double y1, double x2, double y2)
{
	double	x;
	double	y;
	double	x_square;
	double	y_square;

	x = x2 - x1;
	y = y2 - y1;
	x_square = x * x;
	y_square = y * y;
	return (sqrt(x_square + y_square));
}

void	adjust_angle(double *angle)
{
	if (*angle >= 2 * PI)
		*angle -= 2 * PI;
	if (*angle < 0)
		*angle += 2 * PI;
}

void	adjust_x_y(t_data *data, double *x, double *y)
{
	int	max_pos_x;
	int	max_pos_y;

	max_pos_x = (data->map->row_max * IMG_SIZE) - 1;
	max_pos_y = (data->map->col_max * IMG_SIZE) - 1;
	if (*x < IMG_SIZE)
		*x = IMG_SIZE;
	if (*y < IMG_SIZE)
		*y = IMG_SIZE;
	if (*x >= max_pos_x)
		*x = max_pos_x;
	if (*y >= max_pos_y)
		*y = max_pos_y;
	if (*x - (int)*x > 0 && (!((int)*x % IMG_SIZE == IMG_SIZE - 1)))
		*x += 1;
	if (*y - (int)*y > 0 && !((int)*y % IMG_SIZE == IMG_SIZE - 1))
		*y += 1;
}
