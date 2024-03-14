/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:02:56 by jborner           #+#    #+#             */
/*   Updated: 2024/03/14 14:03:12 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	fill_img_color(t_image *img, int color)
{
	for (int y = 0; y < img->width; y++)
	{
		for (int x = 0; x < img->height; x++)
			img_pix_put(img, y, x, color);
	}
}

void	create_frame(t_image *img, int size, int color)
{
	for (int y = 0; y < img->width; y++)
	{
		for (int x = 0; x < img->height; x++)
		{
			if ((x < size || x >= img->height - size) || (y < size || y >= img->width - size))
				img_pix_put(img, y, x, color);
		}
	}
}

unsigned long rgb_to_hex(int rgb[3])
{   
    return ((unsigned long)(rgb[0] & 0xff) << 16) + ((unsigned long)(rgb[1] & 0xff) << 8) + (rgb[2] & 0xff);
}
