/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:51:16 by yubi42            #+#    #+#             */
/*   Updated: 2024/04/24 12:52:59 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	scale_img(t_image **old, t_image **new, int w, int h)
{
	unsigned int	color;
	int				x;
	int				y;
	float			x_ratio;
	float			y_ratio;

	x_ratio = (float)(*old)->width / w;
	y_ratio = (float)(*old)->height / h;
	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			color = get_pixel_img(*old, (int)(x * x_ratio), (int)(y * y_ratio));
			put_pixel_img(*new, x, y, color);
			x++;
		}
		y++;
	}
}

void	resize_same_img(t_data *data, t_image **img, int w, int h)
{
	t_image	*resize;

	resize = create_img(data, NULL, w, h);
	if (!resize)
		close_game(data, "Not able to allocate memory");
	resize->bpp = (*img)->bpp;
	resize->endian = (*img)->endian;
	scale_img(img, &resize, w, h);
	free_img(*img, data->mlx);
	*img = resize;
}

t_image	*resize_img(t_data *data, t_image **old, int w, int h)
{
	t_image	*new_img;

	new_img = create_img(data, NULL, w, h);
	if (!new_img)
		close_game(data, "Not able to allocate memory");
	new_img->bpp = (*old)->bpp;
	new_img->endian = (*old)->endian;
	scale_img(old, &new_img, w, h);
	return (new_img);
}

float	calc_old_x(t_data *data, t_image **old, int x, int y)
{
	return ((x - (*old)->width / 2) * data->player->y_cos + (y - (*old)->height
			/ 2) * data->player->x_sin + (*old)->width / 2);
}

float	calc_old_y(t_data *data, t_image **old, int x, int y)
{
	return (-(x - (*old)->width / 2) * data->player->x_sin + (y - (*old)->height
			/ 2) * data->player->y_cos + (*old)->height / 2);
}

void	rotate_player_img(t_data *data, t_image **old, t_image **new)
{
	int		x;
	int		y;
	float	old_x;
	float	old_y;

	if (*new)
		free_img(*new, data->mlx);
	*new = create_img(data, NULL, (*old)->width, (*old)->height);
	y = 0;
	while (y < (*old)->height)
	{
		x = 0;
		while (x < (*old)->width)
		{
			old_x = calc_old_x(data, old, x, y);
			old_y = calc_old_y(data, old, x, y);
			if (old_x >= 0 && old_x < (*old)->width && old_y >= 0
				&& old_y < (*old)->height)
				put_pixel_img(*new, x, y, get_pixel_img(*old, old_x, old_y));
			x++;
		}
		y++;
	}
}
