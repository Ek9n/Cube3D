/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 17:50:35 by hstein            #+#    #+#             */
/*   Updated: 2024/06/03 13:57:56 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_image	*create_img(t_data *data, char *path, int w, int h)
{
	t_image	*img;

	img = NULL;
	img = malloc(sizeof(t_image));
	if (!img)
		close_game(data, "Not able to allocate memory or wrong img path");
	img->addr = NULL;
	img->img_ptr = NULL;
	if (path)
		img->img_ptr = mlx_xpm_file_to_image(data->mlx, path, &(img->width),
				&(img->height));
	else
	{
		img->img_ptr = mlx_new_image(data->mlx, w, h);
		img->width = w;
		img->height = h;
	}
	img->addr = mlx_get_data_addr(img->img_ptr, &(img->bpp),
			&(img->bytes_per_line), &(img->endian));
	if (!(img->img_ptr || img->addr))
		close_game(data, "Not able to allocate memory for img_ptr or addr");
	return (img);
}

void	create_wall_imgs(t_data *data)
{
	data->texture->no = create_img(data, data->texture->no_path, 0, 0);
	data->texture->so = create_img(data, data->texture->so_path, 0, 0);
	data->texture->we = create_img(data, data->texture->we_path, 0, 0);
	data->texture->ea = create_img(data, data->texture->ea_path, 0, 0);
	if (data->texture->ea->width != IMG_SIZE)
	{
		resize_same_img(data, &data->texture->no, IMG_SIZE, IMG_SIZE);
		resize_same_img(data, &data->texture->so, IMG_SIZE, IMG_SIZE);
		resize_same_img(data, &data->texture->we, IMG_SIZE, IMG_SIZE);
		resize_same_img(data, &data->texture->ea, IMG_SIZE, IMG_SIZE);
	}
}

void	create_goal_img(t_data *data)
{
	if (data->map->player == 'E')
		data->texture->goal = create_img(data, "./img/goal_e.xpm", 0, 0);
	else if (data->map->player == 'W')
		data->texture->goal = create_img(data, "./img/goal_w.xpm", 0, 0);
	else if (data->map->player == 'N')
		data->texture->goal = create_img(data, "./img/goal_n.xpm", 0, 0);
	else if (data->map->player == 'S')
		data->texture->goal = create_img(data, "./img/goal_s.xpm", 0, 0);
	data->texture->black = create_img(data, "./img/black.xpm", 0, 0);
	data->texture->transparent = create_img(data, "./img/transparent.xpm", 0,
			0);
	data->texture->steeringwheel = create_img(data, "./img/steeringwheel.xpm",
			0, 0);
	data->texture->steeringwheel2 = create_img(data, "./img/steeringwheel.xpm",
			0, 0);
	data->texture->carframe = create_img(data, "./img/cockpit.xpm", 0, 0);
	data->texture->carframe2 = resize_img(data, &data->texture->carframe,
			data->width, data->height);
	data->texture->backmirror = create_img(data, "./img/backmirror.xpm", 0, 0);
	data->texture->backmirror2 = create_img(data, "./img/backmirror.xpm", 0, 0);
}

void	create_text_imgs(t_data *data)
{
	data->texture->num0 = create_img(data, "./img/0.xpm", 0, 0);
	data->texture->num1 = create_img(data, "./img/1.xpm", 0, 0);
	data->texture->num2 = create_img(data, "./img/2.xpm", 0, 0);
	data->texture->num3 = create_img(data, "./img/3.xpm", 0, 0);
	data->texture->num4 = create_img(data, "./img/4.xpm", 0, 0);
	data->texture->num5 = create_img(data, "./img/5.xpm", 0, 0);
	data->texture->num6 = create_img(data, "./img/6.xpm", 0, 0);
	data->texture->num7 = create_img(data, "./img/7.xpm", 0, 0);
	data->texture->num8 = create_img(data, "./img/8.xpm", 0, 0);
	data->texture->num9 = create_img(data, "./img/9.xpm", 0, 0);
	data->texture->alpha = create_img(data, "./img/alpha.xpm", 0, 0);
	data->texture->alpha2 = create_img(data, "./img/alpha.xpm", 0, 0);
	data->texture->slash = create_img(data, "./img/slash.xpm", 0, 0);
	data->texture->kmh = create_img(data, "./img/kmh.xpm", 0, 0);
	data->texture->high_score = create_img(data, "./img/highscore.xpm", 0, 0);
	data->texture->your_score = create_img(data, "./img/your_score.xpm", 0, 0);
}

void	mlx_init_game(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		close_game(data, "ERROR");
	data->mlx_win = mlx_new_window(data->mlx, data->width, data->height,
			"cub3d");
	if (data->mlx_win == NULL)
		close_game(data, "ERROR");
	create_wall_imgs(data);
	create_goal_img(data);
	create_text_imgs(data);
	resize_same_img(data, &data->texture->backmirror, 406, 150);
	resize_same_img(data, &data->texture->backmirror2, 406, 150);
	data->texture->game_over = create_img(data, "./img/game_over2.xpm", 0, 0);
	resize_same_img(data, &data->texture->game_over, data->width, data->height);
	if (data->sound_on)
		setup_sounds(data);
}
