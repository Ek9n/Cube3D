/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:58:23 by jborner           #+#    #+#             */
/*   Updated: 2024/04/30 15:12:15 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


void rotate_image(t_data *data, t_image **img, double angle)
{
		// printf("1ANGLE%f\n", angle);

        double radians;
		radians = angle * PI / 180.0;

        // Buffer-Bild erstellen
        t_image *img_rot;
        img_rot = create_img(data, NULL, (*img)->width, (*img)->height);

        for (int y = 0; y < img_rot->height; y++) {
            for (int x = 0; x < img_rot->width; x++) {
                // Berechne die Koordinaten im rotierten Bild relativ zum Zentrum
                int new_x = (x - (*img)->width / 2);
                int new_y = (y - (*img)->height / 2);

                // Rotiere die Koordinaten im rotierten Bild um den Ursprung (0,0)
                int rotated_x = (new_x * cos(radians) - new_y * sin(radians));
                int rotated_y = (new_x * sin(radians) + new_y * cos(radians));

                // Konvertiere die Koordinaten zurück zum Koordinatensystem des ursprünglichen Bildes
                rotated_x += (*img)->width / 2;
                rotated_y += (*img)->height / 2;

                // Überprüfe, ob die neuen Koordinaten innerhalb des Bildes liegen
                if (rotated_x >= 0 && rotated_x < (*img)->width && rotated_y >= 0 && rotated_y < (*img)->height) {
                    // Setze den Pixelwert im rotierten Bild
                    put_pixel_img(img_rot, x, y, get_pixel_img(*img, rotated_x, rotated_y));
                    // put_pixel_img(img_rot, x, y, get_pixel_img(*img, rotated_x, rotated_y));
                    // put_pixel_img(img_rot, rotated_x, rotated_y, get_pixel_img(*img, x, y));
                }
            }
        }

        // free_img(*img, data->mlx);
        // *img = img_rot;
		if (data->texture->steeringwheel2)
			free_img(data->texture->steeringwheel2, data->mlx);
		data->texture->steeringwheel2 = img_rot;
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
			else
				put_img_to_img(minimap->base, data->texture->goal, col * IMG_SIZE, row
					* IMG_SIZE);
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
	minimap->resize = resize_img(data, &minimap->small, minimap->small->width / 2, minimap->small->height / 2);
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

int	render(t_data *data)
{
	// static int	last_dir;
	handle_keys(data);
	render_background(data, data->texture->base_img);
	render_minimap(data, data->texture->minimap);

	put_img_to_img(data->texture->base_img, data->texture->carframe2, 0, 0);
	put_img_to_img(data->texture->base_img, data->texture->minimap->resize, 1400, 650);

	rotate_image(data, &data->texture->steeringwheel, -4 * data->player->rotation);
	ma_sound_set_pitch(&data->sound.motor, data->player->speed[0] / 8);
	// printf("cur speed: %f km/h\n", data->player->speed[0] * 10.0);

	put_img_to_img(data->texture->base_img, data->texture->steeringwheel2, 500, 500);
	if (data->player->dead)
	{
		ma_sound_start(&data->sound.crash);
		put_img_to_img(data->texture->base_img, data->texture->game_over, 200, -200);
	}
	// int flag = 0;
	// if (!flag)
	// {
	// 	data->texture->nums1->addr += 64;
	// 	data->texture->nums1 = resize_img(data, &data->texture->nums, data->texture->nums->width * 3, data->texture->nums->height * 3);
	// 	printf("weite %d\n", data->texture->nums->width);
	// 	flag = 1;
	// }
	put_img_to_img(data->texture->base_img, data->texture->nums, 50, 50);
	mlx_put_image_to_window(data->mlx, data->mlx_win,
				data->texture->base_img->img_ptr, 0, 0);
	usleep(42000);
	return (0);
}
