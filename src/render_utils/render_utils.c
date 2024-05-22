/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:02:56 by jborner           #+#    #+#             */
/*   Updated: 2024/05/22 22:27:59 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	create_frame(t_image *img, int size, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < img->width)
	{
		x = 0;
		while (x < img->height)
		{
			if ((x < size || x >= img->height - size) || (y < size
					|| y >= img->width - size))
				img_pix_put(img, y, x, color);
			++x;
		}
		++y;
	}
}

unsigned long	rgb_to_hex(int rgb[3])
{
	return (((unsigned long)(rgb[0] & 0xff) << 16)
		+ ((unsigned long)(rgb[1] & 0xff) << 8) + (rgb[2] & 0xff));
}

void	render_default_minimap(t_data *data, t_minimap *minimap)
{
	int	col;
	int	row;

	row = -1;
	while (++row < data->map->row_max)
	{
		col = -1;
		while (++col < data->map->col_max)
		{
			if (data->map->grid[row][col] == 0)
				put_img_to_img(minimap->base, minimap->ground, col * IMG_SIZE,
					row * IMG_SIZE);
			else if (data->map->grid[row][col] == 1)
				put_img_to_img(minimap->base, minimap->wall, col * IMG_SIZE, row
					* IMG_SIZE);
			else if (data->map->grid[row][col] != -1)
				put_img_to_img(minimap->base, data->texture->goal, \
					col * IMG_SIZE, row * IMG_SIZE);
		}
	}
}

void	render_minimap(t_data *data, t_minimap *minimap)
{
	render_default_minimap(data, minimap);
	rotate_player_img(data, &minimap->player, &minimap->player_rot);
	put_img_to_img(minimap->base, minimap->player_rot, data->player->y,
		data->player->x);
	cast_rays(data, data->player->angle, 60, data->width);
	copy_to_small(data->player->x, data->player->y, minimap->base,
		minimap->small);
	if (minimap->resize)
		free_img(minimap->resize, data->mlx);
	minimap->resize = resize_img(data, &minimap->small, \
		minimap->small->width / 2, minimap->small->height / 2);
	create_frame(minimap->resize, 5, BLACK);
}

void	render_background(t_data *data, t_image *bg)
{
	int	x;
	int	y;

	x = 0;
	while (x < bg->height)
	{
		y = 0;
		while (y < bg->width)
		{
			if (x < (bg->height / 2))
				img_pix_put(bg, y, x, rgb_to_hex(data->texture->c));
			else
				img_pix_put(bg, y, x, rgb_to_hex(data->texture->f));
			++y;
		}
		++x;
	}
}
