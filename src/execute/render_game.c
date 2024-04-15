/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 13:58:23 by jborner           #+#    #+#             */
/*   Updated: 2024/04/15 18:26:09 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// void rotate_image(t_image *img, double angle)
// {
//     int center_x = img->width / 2;
//     int center_y = img->height / 2;
//     double radians = angle * M_PI / 180.0;

//     char *img_rot = calloc(img->width * img->height, sizeof(char));

//     if (img_rot == NULL) {
//         printf("Fehler: Speicher konnte nicht allokiert werden.\n");
//         return;
//     }
//     for (int y = 0; y < img->height; y++) {
//         for (int x = 0; x < img->width; x++) {
//             // Berechne die Koordinaten im rotierten Bild
//             int new_x = (int)((x - center_x) * cos(radians) - (y - center_y) * sin(radians)) + center_x;
//             int new_y = (int)((x - center_x) * sin(radians) + (y - center_y) * cos(radians)) + center_y;

//             // Überprüfe, ob die neuen Koordinaten innerhalb des Bildes liegen
//             if (new_x >= 0 && new_x < img->width && new_y >= 0 && new_y < img->height) {
//                 // Setze den Pixelwert im rotierten Bild
//                 img_rot[y * img->width + x] = img->addr[new_y * img->width + new_x];
//                 img_rot[y * img->width + x] = img->addr[new_y * img->width + new_x];
//             }
//         }
//     }
//     // free(img->addr); // Freigabe des alten Bilddatenspeichers
//     img->addr = img_rot;
// }

// void	rotate_image(t_data *data, t_image **img, double angle)
// {
// 	int center_x = (*img)->width / 2;
// 	int center_y = (*img)->height / 2;
// 	double radians = angle * PI / 180.0;

//     t_image *img_rot;
// 	img_rot = create_img(data, NULL, (*img)->width, (*img)->height);
// 	for (int y = 0; y < (*img)->height; y++) {
// 		for (int x = 0; x < (*img)->width; x++) {
// 			// Berechne die Koordinaten im rotierten Bild
// 			int new_x = round(((x - center_x) * cos(radians) - (y - center_y) * sin(radians)) + center_x);
// 			int new_y = round(((x - center_x) * sin(radians) + (y - center_y) * cos(radians)) + center_y);
// 			// Überprüfe, ob die neuen Koordinaten innerhalb des Bildes liegen
// 			if (new_x >= 0 && new_x < (*img)->width && new_y >= 0 && new_y < (*img)->height)
// 			{
// 				// Setze den Pixelwert im rotierten Bild
// 				put_pixel_img(img_rot, new_x, new_y, get_pixel_img(*img, x, y));
// 			}
// 		}
// 	}
// 	free_img(*img, data->mlx);
// 	*img = img_rot;
// }

// void rotate_image(t_data *data, t_image **img, double angle)
// {
// 	static double old_angle;
// 	if (old_angle != angle)
// 	{
// 		angle = angle - old_angle;
		
// 		// int center_x = 65;
// 		int center_x = (*img)->width / 2;
// 		// int center_y = 65;
// 		int center_y = (*img)->height / 2;
// 		double radians = angle * PI / 180.0;
// printf("HOEHE:%d\n", center_x);
// printf("WEITE:%d\n", center_y);
		
// 		// Buffer_Bild erstellen
// 		t_image *img_rot;
// 		img_rot = create_img(data, NULL, 129, 129);

// 		for (int y = 0; y < img_rot->height; y++) {
// 			for (int x = 0; x < img_rot->width; x++) {
// 				// Berechne die Koordinaten im rotierten Bild
// 				int new_x = ((x - center_x) * cos(radians) - (y - center_y) * sin(radians) + center_x);
// 				int new_y = ((x - center_x) * sin(radians) + (y - center_y) * cos(radians) + center_y);

// 				// Überprüfe, ob die neuen Koordinaten innerhalb des Bildes liegen
// 				if (new_x >= 0 && new_x < (*img)->width && new_y >= 0 && new_y < (*img)->height) {
// 					// Setze den Pixelwert im rotierten Bild
// 					// put_pixel_img(img_rot, x, y, get_pixel_img(*img, new_x, new_y));
// 					put_pixel_img(img_rot, new_x, new_y, get_pixel_img(*img, x, y));
// 				}
// 			}
// 		}

// 		free_img(*img, data->mlx);
// 		*img = img_rot;
// 		old_angle = angle;
// 	}
// }
void rotate_image(t_data *data, t_image **img, double angle)
{
    static double old_angle;
	printf("new%fold%f\n", angle, old_angle);
    if (old_angle != angle)
    {
        angle = angle - old_angle;

        double radians = angle * PI / 180.0;

        // Größe des rotierten Bildes bestimmen
        int rotated_width = (*img)->width;
        int rotated_height = (*img)->height;

        // Buffer-Bild erstellen
        t_image *img_rot;
        img_rot = create_img(data, NULL, rotated_width, rotated_height);

        for (int y = 0; y < img_rot->height; y++) {
            for (int x = 0; x < img_rot->width; x++) {
                // Berechne die Koordinaten im rotierten Bild relativ zum Zentrum
                int new_x = (x - rotated_width / 2);
                int new_y = (y - rotated_height / 2);

                // Rotiere die Koordinaten im rotierten Bild um den Ursprung (0,0)
                int rotated_x = (int)(new_x * cos(radians) - new_y * sin(radians));
                int rotated_y = (int)(new_x * sin(radians) + new_y * cos(radians));

                // Konvertiere die Koordinaten zurück zum Koordinatensystem des ursprünglichen Bildes
                rotated_x += rotated_width / 2;
                rotated_y += rotated_height / 2;

                // Überprüfe, ob die neuen Koordinaten innerhalb des Bildes liegen
                if (rotated_x >= 0 && rotated_x < (*img)->width && rotated_y >= 0 && rotated_y < (*img)->height) {
                    // Setze den Pixelwert im rotierten Bild
                    put_pixel_img(img_rot, x, y, get_pixel_img(*img, rotated_x, rotated_y));
                }
            }
        }

        free_img(*img, data->mlx);
        *img = img_rot;
        old_angle = angle;
    }
}


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

		put_img_to_img(data->texture->base_img, data->texture->carframe2, 0, 0);
		put_img_to_img(data->texture->base_img, data->texture->minimap->resize, 1500, 600);

		// static bool flag;
		// if (flag == 0)
		// printf("angle:%lf", data->player->angle);
		rotate_image(data, &data->texture->steeringwheel, 0);
		// if (data->keys[XK_Left])
		// {

			rotate_image(data, &data->texture->steeringwheel, data->rot[XK_Left]);
		// }
		// else if (data->keys[XK_Right])
		// {

		// 	rotate_image(data, &data->texture->steeringwheel, -data->rot[XK_Right]);
		// }
		// flag = 1;
		put_img_to_img(data->texture->base_img, data->texture->steeringwheel, 800, 800);
		
		mlx_put_image_to_window(data->mlx, data->mlx_win,
				data->texture->base_img->img_ptr, 0, 0);
	}
	return (0);
}
