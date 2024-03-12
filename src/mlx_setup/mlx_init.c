/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 14:29:57 by hstein            #+#    #+#             */
/*   Updated: 2024/03/12 14:36:41 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

t_img    *create_img(t_data *data, char *path, int w, int h)
{
    t_img *img;

    img = NULL;
    img = malloc(sizeof(t_img));
    if (!img)
        close_game(data, "Not able to allocate memory or wrong img path");
    if (path)
        img->img_ptr = mlx_xpm_file_to_image(data->mlx, path, &(img->width), &(img->height));
    else
    {
        img->img_ptr = mlx_new_image(data->mlx, w, h);
        img->width = w;
        img->height = h;
    }
    img->addr = mlx_get_data_addr(img->img_ptr, &(img->bpp), &(img->bytes_per_line), &(img->endian));
    if(!(img->img_ptr || img->addr))
        close_game(data, "Not able to allocate memory for img_ptr or addr");
    return (img);
}

void    mlx_init_game(t_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
        close_game(data, "ERROR");
		
	data->mlx_win = mlx_new_window(data->mlx, data->width, data->height, "cub3d");
	if (data->mlx_win == NULL)
		close_game(data, "ERROR");

	// data->textures->no_path = mlx_new_image(data->mlx, WIDTH, HEIGHT);
    data->texture->no = create_img(data, data->texture->no_path, 0, 0);
    data->texture->so = create_img(data, data->texture->so_path, 0, 0);
    data->texture->we = create_img(data, data->texture->we_path, 0, 0);
    data->texture->ea = create_img(data, data->texture->ea_path, 0, 0);
}
