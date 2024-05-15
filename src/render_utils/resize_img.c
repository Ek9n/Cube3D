/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:51:16 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/15 15:51:23 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	scale_img(t_image **old, t_image **new, int w, int h)
{
	unsigned int	color;
	int				x;
	int				y;
	double			x_ratio;
	double			y_ratio;

	x_ratio = (double)(*old)->width / w;
	y_ratio = (double)(*old)->height / h;
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
