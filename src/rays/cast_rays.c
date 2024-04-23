/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:54:28 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/23 09:59:59 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
to draw rays into map add in the beginning of do_row_step/do_col_step:
 put_pixel_img(data->texture->minimap->base, (int)ray->row_y, (int)ray->row_x,
	GREEN);
 */

int	do_row_step(t_data *data, t_ray *ray)
{
	if (wall_found(data, ray->row_x, ray->row_y))
	{
		ray->ray_len = ray->dis_row;
		return (1);
	}
	ray->row_x += ray->row_step_x;
	ray->row_y += ray->row_step_y;
	ray->dis_row = distance(ray->x, ray->y, ray->row_x, ray->row_y);
	return (0);
}

int	do_col_step(t_data *data, t_ray *ray)
{
	if (wall_found(data, ray->col_x, ray->col_y))
	{
		ray->ray_len = ray->dis_col;
		return (1);
	}
	ray->col_x += ray->col_step_x;
	ray->col_y += ray->col_step_y;
	ray->dis_col = distance(ray->x, ray->y, ray->col_x, ray->col_y);
	return (0);
}

void	cast_ray(t_data *data, float angle, int x, int y)
{
	adjust_angle(&angle);
	init_check_ray(&data->ray, angle, x, y);
	while (1)
	{
		if (data->ray.row_step > 0 && data->ray.dis_row <= data->ray.dis_col)
		{
			if (do_row_step(data, &data->ray))
				break ;
		}
		else
		{
			if (do_col_step(data, &data->ray))
				break ;
		}
	}
}

void	generate_vertical(t_data *data, int i, float angle_step, int sign)
{
	float	len;
	float	j;
	float	k;
	int		l;
	int		i2;

	l = i - ((data->ray.ray_amount / 2) - data->ray.ray_amount / 10) + 1;
	i2 = i;
	if (l > 0)
		i2 -= 0.0005 * (l * l);
	len = data->height * IMG_SIZE / (data->ray.ray_len * cos(angle_step * i2));
	j = 0;
	k = 0;
	while (j <= len)
	{
		put_pixel_img(data->texture->base_img, (data->width / 2) + (i * sign),
			(data->height / 2) - (len / 2) + j, get_pixel_img(data->ray.img,
				data->ray.img_col, k));
		k += IMG_SIZE / len;
		j++;
	}
}

void	cast_rays(t_data *data, float angle, int deg, int amount)
{
	int		start_x;
	int		start_y;
	int		i;
	float	total;
	float	step;

	start_x = data->player->x + (data->texture->minimap->player->height / 2);
	start_y = data->player->y + (data->texture->minimap->player->width / 2);
	total = deg * (PI / 180.0);
	step = total / amount;
	data->ray.ray_amount = amount;
	i = 0;
	while (i < amount / 2)
	{
		cast_ray(data, angle + (step * i), start_x, start_y);
		generate_vertical(data, i, step, 1);
		if (i)
		{
			cast_ray(data, angle - (step * i), start_x, start_y);
			generate_vertical(data, i, step, -1);
		}
		i++;
	}
}
