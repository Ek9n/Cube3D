/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:58:23 by jborner           #+#    #+#             */
/*   Updated: 2024/04/08 14:56:04 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// #define WALL_HEIGHT 100 // Höhe der Wand in Bildschirmpunkten
// #define VIEW_DISTANCE 200 // Maximale Betrachtungsentfernung
// // Funktion zum Rendern einer vertikalen Wand
// void render_wall(int wall_distance) {
//     // Skalieren Sie die Wandhöhe basierend auf dem Abstand des Betrachters zur Wand
//     int wall_height = WALL_HEIGHT * VIEW_DISTANCE / wall_distance;



void	render_minimap(t_data *data, t_minimap *minimap)
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
		}
	}
	rotate_img(data, &minimap->player, &minimap->player_rot);
	put_img_to_img(minimap->base, minimap->player_rot, data->player->y,
		data->player->x);
	cast_rays(data, data->player->angle , 90, data->width);
	copy_to_small(data->player->x, data->player->y, minimap->base,
		minimap->small);
	if (minimap->resize)
		free_img(minimap->resize, data->mlx);
	minimap->resize = resize_img(data, &minimap->small, data->width
		/ minimap->resize_value, data->width / minimap->resize_value);
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


/* int	new_render_req(t_data *data)
{
	if (data->keys[XK_Right] || data->keys[XK_d]
		|| data->rot[XK_Right] > ROT_MIN || data->keys[XK_Left]
		|| data->keys[XK_a] || data->rot[XK_Left] > ROT_MIN || data->keys[XK_Up]
		|| data->keys[XK_w] || data->rot[XK_Up] > ROT_MIN || data->keys[XK_Down]
		|| data->keys[XK_s] || data->rot[XK_Down] > ROT_MIN)
		return (1);
	return (0);
}
 */

int	render(t_data *data)
{
	if (!remote_delay_ms(10))
	{
		handle_keys(data);
		render_background(data, data->texture->base_img);
		delay_reset_all(data->keys, data->delay, data->rot);
		render_minimap(data, data->texture->minimap);
		put_img_to_img(data->texture->base_img, data->texture->minimap->resize,
			10, 10);
		mlx_put_image_to_window(data->mlx, data->mlx_win,
				data->texture->base_img->img_ptr, 0, 0);
	}
	return (0);
}
