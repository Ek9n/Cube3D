/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 17:54:28 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/08 14:43:11 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int do_row_step(t_data *data, t_check_ray *ray)
{
	put_pixel_img(data->texture->minimap->base, (int)ray->row_y, (int)ray->row_x, GREEN);
	if (wall_found(data, ray->row_x, ray->row_y))
	{
		data->ray.ray_len = ray->dis_row;
		return (1);
	}
	ray->row_x += ray->row_step_x;
	ray->row_y += ray->row_step_y;
	ray->dis_row = distance(ray->x, ray->y, ray->row_x, ray->row_y);
	return (0);
}

int do_col_step(t_data *data, t_check_ray *ray)
{
	put_pixel_img(data->texture->minimap->base, (int)ray->col_y, (int)ray->col_x, GREEN);
	if (wall_found(data, ray->col_x, ray->col_y))
	{
		data->ray.ray_len = ray->dis_col;
		return (1);
	}
	ray->col_x += ray->col_step_x;
	ray->col_y += ray->col_step_y;
	ray->dis_col = distance(ray->x, ray->y, ray->col_x, ray->col_y);
	return (0);
}

void	cast_ray(t_data *data, float angle, int x, int y)
{
	t_check_ray	ray;

	adjust_angle(&angle);
	init_check_ray(&ray, angle, x, y);
	while (1)
	{
		if(ray.row_step > 0 && ray.dis_row <= ray.dis_col)
		{
			if(do_row_step(data, &ray))
				break ;
		}	
		else
		{
			if(do_col_step(data, &ray))
			break ;
		}
	}
}

void	generate_vertical(t_data *data, t_ray ray, int i)
{
	double	len = data->height * IMG_SIZE / ray.ray_len;
	double	j = 0;
	double	k = 0;
	double	step = 64.0 / len;
	t_image *IMG;
	// int	len = data->height * 20 / ray.ray_len;
	// printf("len %i\n", len);
	// printf(" ray.ray_distance%d\n", ray.ray_distance);
	if (ray.img_dir == 'N')
		IMG = data->texture->no;
	else if (ray.img_dir == 'S')
		IMG = data->texture->so;
	else if (ray.img_dir == 'W')
		IMG = data->texture->we;
	else if (ray.img_dir == 'E')
		IMG = data->texture->ea;
	else if (ray.img_dir == 'B')
		IMG = data->texture->black;
	else
		IMG = NULL;
	while (j <= len)
	{
		put_pixel_img(data->texture->base_img, i, (data->height / 2) - (len / 2) + j, 
			get_pixel_img(IMG, ray.img_col, k));
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
	float	current_angle;

	start_x = data->player->x + (data->texture->minimap->player->height / 2);
	start_y = data->player->y + (data->texture->minimap->player->width / 2);
	total = deg * (PI / 180.0);
	step = total / amount;
    current_angle = angle - (total / 2);
	// cast_ray(data, angle, start_x, start_y);
	// draw_ray_into_base(data, ray_len, i);
	data->ray.ray_amount = amount;
	data->ray.ray_distance = data->width / amount;
	// printf("DISTANCE:%d\n", data->ray.ray_distance);

	i = 0;
    while (i < amount) 
	{
		// printf("1i:%d\n", i);
		// printf("1total:%f\n", total);
		// printf("1step:%f\n", step);
		// printf("1step*i:%f\n", step * i);
		// printf("1anglestep:%f\n", angle + step * i);
        // cast_ray(data, angle + step * i, start_x, start_y);
        // cast_ray(data, angle + (step * i), start_x, start_y);
        cast_ray(data, angle + (step * i) - total/2 + step/2, start_x, start_y);
		generate_vertical(data, data->ray, i);
		// if (i > 0)
		// {
		// 	cast_ray(data, angle - step * i, start_x, start_y);
		// 	generate_vertical(data, data->ray, i);
		// }

        current_angle += step;
		i++;
    }
	// printf("%c\n", data->ray.img_dir);
}
