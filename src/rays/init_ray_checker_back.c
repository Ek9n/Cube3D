/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ray_checker_back.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:06:40 by jborner           #+#    #+#             */
/*   Updated: 2024/06/03 14:12:16 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	init_ray_steps_back(t_ray_back *ray)
{
	if (ray->fabs_sin < EPSILON)
		ray->row_step = 0;
	else
		ray->row_step = IMG_SIZE / ray->fabs_sin;
	if (ray->fabs_cos < EPSILON)
		ray->col_step = 0;
	else
		ray->col_step = IMG_SIZE / ray->fabs_cos;
	if (ray->fabs_sin < EPSILON)
		ray->first_row_step = 0;
	else if (ray->angle >= PI)
		ray->first_row_step = (IMG_SIZE - (IMG_SIZE - (ray->x % IMG_SIZE)))
			/ ray->fabs_sin;
	else
		ray->first_row_step = (IMG_SIZE - (ray->x % IMG_SIZE)) / ray->fabs_sin;
	if (ray->fabs_cos < EPSILON)
		ray->first_col_step = 0;
	else if (ray->angle >= 0.5 * PI && ray->angle < 1.5 * PI)
		ray->first_col_step = (IMG_SIZE - (IMG_SIZE - (ray->y % IMG_SIZE)))
			/ ray->fabs_cos;
	else
		ray->first_col_step = (IMG_SIZE - (ray->y % IMG_SIZE)) / ray->fabs_cos;
}

void	init_next_steps_back(t_ray_back *ray)
{
	if (ray->first_row_step != 0)
	{
		ray->row_x = ray->x + (ray->first_row_step * ray->sin);
		ray->row_y = ray->y + (ray->first_row_step * ray->cos);
	}
	else
	{
		ray->row_x = ray->x + ray->row_step_x;
		ray->row_y = ray->y + ray->row_step_y;
	}
	if (ray->first_col_step != 0)
	{
		ray->col_x = ray->x + (ray->first_col_step * ray->sin);
		ray->col_y = ray->y + (ray->first_col_step * ray->cos);
	}
	else
	{
		ray->col_x = ray->x + ray->col_step_x;
		ray->col_y = ray->y + ray->col_step_y;
	}
}

void	init_check_ray_back(t_ray_back *ray, double angle, int x, int y)
{
	ray->x = x;
	ray->y = y;
	ray->angle = angle;
	ray->sin = sin(angle);
	ray->cos = cos(angle);
	ray->fabs_sin = fabs(ray->sin);
	ray->fabs_cos = fabs(ray->cos);
	init_ray_steps_back(ray);
	ray->row_step_x = ray->row_step * ray->sin;
	ray->row_step_y = ray->row_step * ray->cos;
	ray->col_step_x = ray->col_step * ray->sin;
	ray->col_step_y = ray->col_step * ray->cos;
	init_next_steps_back(ray);
	ray->dis_row = distance(ray->x, ray->y, ray->row_x, ray->row_y);
	ray->dis_col = distance(ray->x, ray->y, ray->col_x, ray->col_y);
	ray->first_col = 1;
}
