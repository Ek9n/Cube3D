/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 17:44:20 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/22 22:34:35 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	fill_img_color(t_image *img, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < img->width)
	{
		x = 0;
		while (x < img->height)
		{
			img_pix_put(img, y, x, color);
			++x;
		}
		++y;
	}
}

void	img_pix_put(t_image *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->bytes_per_line + x * (img->bpp / 8));
	*(int *)pixel = color;
}

void	put_pixel_img(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (color == (int)0x000000)
		return ;
	if (x >= 0 && y >= 0 && x < img->width && y < img->height)
	{
		dst = img->addr + (y * img->bytes_per_line + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

unsigned int	get_pixel_img(t_image *img, int x, int y)
{
	return (*(unsigned int *)((img->addr + (y * img->bytes_per_line) \
		+ (x * img->bpp / 8))));
}

void	put_img_to_img(t_image *dst, t_image *src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < src->width)
	{
		j = 0;
		while (j < src->height)
		{
			put_pixel_img(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}
