/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_nums_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:15:38 by hstein            #+#    #+#             */
/*   Updated: 2024/05/22 22:19:06 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	put_laptime_ms(t_data *data, int w, int h, long long score)
{
	put_num_to_baseimg(data, score, w, h);
}

void	put_laptime_ms_rest(t_data *data, int w, int h, long long score)
{
	put_num_to_baseimg(data, score % 1000, w, h);
}

void	put_laptime_s(t_data *data, int w, int h, long long score)
{
	put_num_to_baseimg(data, score / 1000, w, h);
}

void	put_laptime(t_data *data, int w, int h, int highscore)
{
	long long	score;
	t_image		*resize;

	if (!data->end_reached)
		data->cur_score = get_elapsed_time_ms(&data->start_time);
	score = data->cur_score;
	if (highscore)
		score = data->highscore;
	resize = resize_img(data, &data->texture->transparent, 145, 115);
	put_laptime_ms_rest(data, w - (resize->width / 2), h + 50, score);
	put_laptime_s(data, w - (resize->width / 2), h, score);
	create_frame(data->texture->transparent, 3, WHITE);
	put_img_to_img(data->texture->base_img, resize, w - (resize->width / 2), h);
	free_img(resize, data->mlx);
}

void	put_highscore(t_data *data, int w, int h)
{
	int	i;

	put_img_to_img(data->texture->base_img, data->texture->high_score, w, h);
	h += 60;
	i = -1;
	while (++i < SCORE_ENTRYS)
	{
		put_str(data, data->names[i], w + 20, h + 3);
		put_num_to_baseimg(data, data->score[i], w, h + 10);
		h += 70;
	}
}
