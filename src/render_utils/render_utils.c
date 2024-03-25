/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 14:02:56 by jborner           #+#    #+#             */
/*   Updated: 2024/03/25 15:46:42 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	remote_delay_ms(size_t delay)
{
	size_t			time_us;
	static size_t	time_tmp;
	static size_t	time_cnt;
	struct timeval	tv;

	delay *= 1000;
	gettimeofday(&tv, NULL);
	time_us = tv.tv_usec;
	if (time_tmp > time_us)
		time_cnt += 1000000 - time_tmp + time_us;
	else
		time_cnt += time_us - time_tmp;
	time_tmp = time_us;
	if ((time_cnt % (delay * 2)) < delay)
		return (1);
	return (0);
}

size_t	delay_ms(void)
{
	static bool		flag;
	static size_t	counter;
	size_t			delay;

	delay = 10;
	if (remote_delay_ms(delay))
		flag = true;
	if (flag == true && !remote_delay_ms(delay))
	{
		counter += 50;
		flag = false;
	}
	return (counter);
}

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
