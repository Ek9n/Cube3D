/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_score_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:15:38 by hstein            #+#    #+#             */
/*   Updated: 2024/05/22 22:47:31 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	put_single_num(t_data *data, unsigned int num, int w, int h)
{
	if (num == 0)
		put_img_to_img(data->texture->base_img, data->texture->num0, w, h);
	else if (num == 1)
		put_img_to_img(data->texture->base_img, data->texture->num1, w, h);
	else if (num == 2)
		put_img_to_img(data->texture->base_img, data->texture->num2, w, h);
	else if (num == 3)
		put_img_to_img(data->texture->base_img, data->texture->num3, w, h);
	else if (num == 4)
		put_img_to_img(data->texture->base_img, data->texture->num4, w, h);
	else if (num == 5)
		put_img_to_img(data->texture->base_img, data->texture->num5, w, h);
	else if (num == 6)
		put_img_to_img(data->texture->base_img, data->texture->num6, w, h);
	else if (num == 7)
		put_img_to_img(data->texture->base_img, data->texture->num7, w, h);
	else if (num == 8)
		put_img_to_img(data->texture->base_img, data->texture->num8, w, h);
	else if (num == 9)
		put_img_to_img(data->texture->base_img, data->texture->num9, w, h);
}

void	put_num(t_data *data, unsigned int num, int *w_h, int pos)
{
	char	base[11];

	ft_memcpy(base, "0123456789", 11);
	if (num >= 10)
		put_num(data, num / 10, w_h, pos - 1);
	put_single_num(data, base[num % 10] - 48, w_h[0] + (pos * 40), w_h[1]);
}

void	put_num_to_baseimg(t_data *data, unsigned int num, int w, int h)
{
	unsigned int	num_tmp;
	int				pos;
	int				w_h[2];

	w_h[0] = w;
	w_h[1] = h;
	num_tmp = num;
	pos = 0;
	while (num_tmp > 9)
	{
		num_tmp /= 10;
		pos++;
	}
	put_num(data, num, w_h, pos);
}

void	put_kmh(t_data *data, unsigned int num, int w, int h)
{
	put_num_to_baseimg(data, num, w, h);
	put_img_to_img(data->texture->base_img, data->texture->kmh, w, h + 64);
}

long long	get_elapsed_time_ms(struct timeval *start_time)
{
	struct timeval	current_time;
	long long		elapsed_time_ms;

	gettimeofday(&current_time, NULL);
	if (start_time->tv_sec == 0 && start_time->tv_usec == 0)
		*start_time = current_time;
	elapsed_time_ms = (current_time.tv_sec - start_time->tv_sec) * 1000LL + \
		(current_time.tv_usec - start_time->tv_usec) / 1000LL;
	return (elapsed_time_ms);
}
