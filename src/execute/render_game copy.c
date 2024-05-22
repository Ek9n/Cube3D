/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:58:23 by jborner           #+#    #+#             */
/*   Updated: 2024/05/22 22:03:57 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	rotate_wheel(t_rotate *rot)
{
	rot->y = -1;
	rot->x = -1;
	while (++(rot->y) < rot->img_rot->height)
	{
		while (++(rot->x) < rot->img_rot->width)
		{
			rot->new_x = (rot->x - (*rot->img)->width / 2);
			rot->new_y = (rot->y - (*rot->img)->height / 2);
			rot->rotated_x = (rot->new_x * cos(rot->radians) - rot->new_y * \
				sin(rot->radians));
			rot->rotated_y = (rot->new_x * sin(rot->radians) + rot->new_y * \
				cos(rot->radians));
			rot->rotated_x += (*rot->img)->width / 2;
			rot->rotated_y += (*rot->img)->height / 2;
			if (rot->rotated_x >= 0 && rot->rotated_x < (*rot->img)->width && \
				rot->rotated_y >= 0 && rot->rotated_y < (*rot->img)->height)
				put_pixel_img(rot->img_rot, rot->x, rot->y, \
					get_pixel_img(*rot->img, rot->rotated_x, rot->rotated_y));
		}
		rot->x = -1;
	}
}

void	rotate_stuff(t_data *data, t_image **img, double angle, int opt)
{
	t_rotate	rot;

	rot.img = img;
	rot.radians = angle * PI / 180.0;
	rot.img_rot = create_img(data, NULL, (*img)->width, (*img)->height);
	if (opt == 1)
		rotate_wheel(&rot);
	put_img_to_img(data->texture->base_img, rot.img_rot, 500, 500);
	free_img(rot.img_rot, data->mlx);
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
	char	base[] = "0123456789";

	if (num >= 10)
		put_num(data, num / 10, w_h, pos - 1);
	put_single_num(data, base[num % 10] - 48, w_h[0] + (pos * 40), w_h[1]);
}

void	put_num_to_baseimg(t_data *data, unsigned int num, int w, int h)
{
	unsigned int num_tmp;
	int	pos;
	int	w_h[2];

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
	struct		timeval current_time;
	long long	elapsed_time_ms;

	gettimeofday(&current_time, NULL);
	if (start_time->tv_sec == 0 && start_time->tv_usec == 0)
		*start_time = current_time;
	elapsed_time_ms = (current_time.tv_sec - start_time->tv_sec) * 1000LL + \
		(current_time.tv_usec - start_time->tv_usec) / 1000LL;
	return (elapsed_time_ms);
}

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
	long long score;

	t_image	*resize;
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

void	goal_logic(t_data *data)
{
	if(data->player->x >= IMG_SIZE && data->player->y >= IMG_SIZE && data->player->x <= data->map->row_max * IMG_SIZE - IMG_SIZE && data->player->y <= data->map->col_max * IMG_SIZE - IMG_SIZE)
	{
		if(data->map->grid[(int)(data->player->x + (IMG_SIZE / 2)) / IMG_SIZE][(int)(data->player->y + (IMG_SIZE / 2)) / IMG_SIZE] == 2)
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
	if (data->round == ROUNDS && !data->end_reached)
	{
		if (data->highscore == 0 || data->cur_score < data->highscore)
			data->highscore = data->cur_score;
		safe_score(data);
		data->end_reached = 1;
	}
	if (data->end_reached)
	{
		put_img_to_img(data->texture->base_img, data->texture->your_score,  data->width / 2 - (data->texture->your_score->width / 2), 100);
		put_num_to_baseimg(data, data->highscore,  data->width / 2 - (data->texture->your_score->width / 2), 160);
		put_highscore(data, data->width / 2 - (data->texture->high_score->width / 2), 260);
	}
	put_img_to_img(data->texture->base_img, data->texture->slash, 60, 20);
	put_img_to_img(data->texture->base_img, data->texture->num2, 100, 20);
}

void	death_check(t_data *data)
{
	static bool	flag;

	if (data->player->dead)
	{
		if (data->sound_on && !flag)
			ma_sound_start(&data->sound.crash);
		put_img_to_img(data->texture->base_img, data->texture->game_over, 200, -200);
		flag = true;
	}
}

void	put_letter(t_data *data, char letter, int w, int h)
{
	int	start;
	int	end;
	int	i;
	int	j;
	int size;

	start = (letter - 65) * data->texture->alpha->height;
	end = (letter - 65) * data->texture->alpha->height + data->texture->alpha->height;
	size = 2;
	i = 0;
	while (i < data->texture->alpha->height)
	{
		j = 0;
		while (j < data->texture->alpha->height)
		{
			put_pixel_img(data->texture->base_img, w + j, h + i, get_pixel_img(data->texture->alpha, start + j, i));
			j++;
		}
		i++;
	}
}

void	put_str(t_data *data, char *str, int w, int h)
{
	int		i;
	char	c;

	w -= 2;
	i = -1;
	while (str[++i])
	{
		c = str[i];
		if (c >= 'a' && c <= 'z')
			c -= 32;
		else if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z'))
			c = 'X';
		put_letter(data, c, w + i * 10, h);
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
	put_img_to_img(data->texture->base_img, data->texture->minimap->resize, 1400, 650);
	rotate_stuff(data, &data->texture->steeringwheel, -4 * data->player->rotation, 1);
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
