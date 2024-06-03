/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:14:12 by jborner           #+#    #+#             */
/*   Updated: 2024/06/03 14:14:28 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	put_pixel_img2(t_image *img, int x, int y, int color)
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

void	put_img_to_img2(t_image *dst, t_image *src, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < dst->width)
	{
		j = 0;
		while (j < dst->height)
		{
			if (get_pixel_img(dst, x + i, y + j) == 0x22B14C)
				put_pixel_img2(dst, x + i, y + j, get_pixel_img(src, i, j));
			j++;
		}
		i++;
	}
}
