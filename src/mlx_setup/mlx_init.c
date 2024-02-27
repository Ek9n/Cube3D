/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:29:57 by hstein            #+#    #+#             */
/*   Updated: 2024/02/27 14:48:08 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void create_img(t_data *data, void **img, char *path)
{
    int img_width;
    int img_height;

    img_width = WIDTH;
    img_height = HEIGHT;
    *img = mlx_xpm_file_to_image(data->mlx, path, &img_width, &img_height);
    if (!*img)
        close_game(data, "Not able to allocate memory or wrong img path");
}

void	mlx_init_data(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
        close_game(data, "ERROR");
		
	data->mlx_win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cub3d");
	if (data->mlx_win == NULL)
		close_game(data, "ERROR");

	// data->textures->no_path = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    create_img(data, &data->texture->no_addr, data->texture->no_path);
    create_img(data, &data->texture->so_addr, data->texture->so_path);
    create_img(data, &data->texture->we_addr, data->texture->we_path);
    create_img(data, &data->texture->ea_addr, data->texture->ea_path);
}