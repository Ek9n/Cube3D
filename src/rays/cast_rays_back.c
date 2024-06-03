/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:01:10 by jborner           #+#    #+#             */
/*   Updated: 2024/06/03 14:12:34 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	do_row_step_back(t_data *data, t_ray_back *ray)
{
	if (wall_found_back(data, ray->row_x, ray->row_y))
		return (1);
	ray->row_x += ray->row_step_x;
	ray->row_y += ray->row_step_y;
	ray->dis_row = distance(ray->x, ray->y, ray->row_x, ray->row_y);
	return (0);
}

int	do_col_step_back(t_data *data, t_ray_back *ray)
{
	if (wall_found_back(data, ray->col_x, ray->col_y))
	{
		ray->ray_len = ray->dis_col;
		return (1);
	}
	ray->col_x += ray->col_step_x;
	ray->col_y += ray->col_step_y;
	ray->dis_col = distance(ray->x, ray->y, ray->col_x, ray->col_y);
	return (0);
}

void	cast_ray_back(t_data *data, double angle, int x, int y)
{
	adjust_angle(&angle);
	init_check_ray_back(&data->ray_back, angle, x, y);
	while (1)
	{
		if (data->ray_back.row_step > 0
			&& (data->ray_back.dis_row <= data->ray_back.dis_col
				|| data->ray_back.dis_col == 0))
		{
			if (do_row_step_back(data, &data->ray_back))
				break ;
		}
		else
		{
			if (do_col_step_back(data, &data->ray_back))
				break ;
		}
	}
}

void	generate_vertical2(t_data *data, int i, double angle_step, int sign)
{
	double	len;
	double	j;
	double	k;
	double	l;
	double	i2;

	l = i - ((data->ray_back.ray_amount / 2) - data->ray_back.ray_amount / 10)
		+ 1;
	i2 = i;
	if (l > 0)
		i2 -= 0.0005 * (l * l);
	len = data->height * IMG_SIZE / (data->ray_back.ray_len * cos(angle_step
				* i2));
	j = 0;
	k = 0;
	while (j <= len)
	{
		put_pixel_img(data->texture->base_img2, (data->width / 2) + (i * sign),
			(data->height / 2) - (len / 2) + j,
			get_pixel_img(data->ray_back.img, data->ray_back.img_col, k));
		k += IMG_SIZE / len;
		j++;
	}
}

void	cast_rays2(t_data *data, double angle, int deg, int amount)
{
	int		start_x;
	int		start_y;
	int		i;
	double	total;
	double	step;

	start_x = data->player->x + (data->texture->minimap->player->height / 2);
	start_y = data->player->y + (data->texture->minimap->player->width / 2);
	total = deg * (PI / 180.0);
	step = total / amount;
	data->ray_back.ray_amount = amount;
	i = 0;
	while (i < amount / 2)
	{
		cast_ray_back(data, angle + (step * i), start_x, start_y);
		generate_vertical2(data, i, step, 1);
		if (i)
		{
			cast_ray_back(data, angle - (step * i), start_x, start_y);
			generate_vertical2(data, i, step, -1);
		}
		i++;
	}
}
