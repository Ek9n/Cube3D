/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:54:28 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/16 15:59:26 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	do_row_step(t_data *data, t_ray *ray)
{
	// put_pixel_img(data->texture->minimap->base, (int)ray->row_y,
	// 	(int)ray->row_x, GREEN);
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
	// put_pixel_img(data->texture->minimap->base, (int)ray->col_y,
	// 	(int)ray->col_x, GREEN);
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
	data->ray.raw_angle = angle;
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

void	generate_vertical(t_data *data, t_ray ray, int i, t_image *img, int sign, float angle_step)
{
	double	len;
	double	j;
	double	k;
	double	step;

	len = data->height * 60 / (ray.ray_len * cos(angle_step * (i - (0.185 * i)) * sign));
	j = 0;
	k = 0;
	step = IMG_SIZE / len;
	while (j <= len)
	{
		put_pixel_img(data->texture->base_img, (data->width / 2) + (i * sign), (data->height / 2) - (len / 2)
			+ j, get_pixel_img(img, ray.img_col, k));
		k += step;
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
		generate_vertical(data, data->ray, i, data->ray.img, 1, step);
		cast_ray(data, angle - (step * i), start_x, start_y);
		generate_vertical(data, data->ray, i, data->ray.img, -1, step);
		i++;
	}
}
