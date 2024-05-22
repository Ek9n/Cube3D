/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:58:23 by jborner           #+#    #+#             */
/*   Updated: 2024/05/22 22:46:04 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	goal_logic_continue(t_data *data)
{
	if (data->round == ROUNDS && !data->end_reached)
	{
		if (data->highscore == 0 || data->cur_score < data->highscore)
			data->highscore = data->cur_score;
		safe_score(data);
		data->end_reached = 1;
	}
	if (data->end_reached)
	{
		put_img_to_img(data->texture->base_img, data->texture->your_score, \
			data->width / 2 - (data->texture->your_score->width / 2), 100);
		put_num_to_baseimg(data, data->highscore, data->width / \
			2 - (data->texture->your_score->width / 2), 160);
		put_highscore(data, data->width / 2 - \
			(data->texture->high_score->width / 2), 240);
	}
	put_img_to_img(data->texture->base_img, data->texture->slash, 60, 20);
	put_img_to_img(data->texture->base_img, data->texture->num2, 100, 20);
}

void	goal_logic(t_data *data)
{
	if (data->player->x >= IMG_SIZE && data->player->y >= IMG_SIZE && \
		data->player->x <= data->map->row_max * IMG_SIZE - IMG_SIZE && \
		data->player->y <= data->map->col_max * IMG_SIZE - IMG_SIZE)
	{
		if (data->map->grid[(int)(data->player->x + (IMG_SIZE / 2)) / \
			IMG_SIZE][(int)(data->player->y + (IMG_SIZE / 2)) / IMG_SIZE] == 2)
		{
			if (!data->round_touch)
				data->round++;
			data->round_touch = 1;
		}
		else
			data->round_touch = 0;
	}
	if (data->round <= 0)
		put_num_to_baseimg(data, 0, 20, 20);
	else if (data->round >= ROUNDS)
		put_num_to_baseimg(data, 2, 20, 20);
	else 
		put_num_to_baseimg(data, data->round, 20, 20);
	goal_logic_continue(data);
}

void	death_check(t_data *data)
{
	static bool	flag;

	if (data->player->dead)
	{
		if (data->sound_on && !flag)
			ma_sound_start(&data->sound.crash);
		put_img_to_img(data->texture->base_img, \
			data->texture->game_over, 200, -200);
		flag = true;
	}
}

int	render(t_data *data)
{
	handle_keys(data);
	if (data->sound_on)
		ma_sound_set_pitch(&data->sound.motor, data->player->speed[0] / 8);
	render_background(data, data->texture->base_img);
	render_minimap(data, data->texture->minimap);
	put_img_to_img(data->texture->base_img, data->texture->carframe2, 0, 0);
	put_img_to_img(data->texture->base_img, \
		data->texture->minimap->resize, 1400, 650);
	rotate_stuff(data, &data->texture->steeringwheel, \
		-4 * data->player->rotation, 1);
	death_check(data);
	put_kmh(data, data->player->speed[0] * 5, 1200, 870);
	if (!data->end_reached)
		put_laptime(data, 1750, 100, 0);
	goal_logic(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->texture->base_img->img_ptr, 0, 0);
	fps_delay(60);
	return (0);
}
