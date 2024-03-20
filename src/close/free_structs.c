/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:50:16 by yubi42            #+#    #+#             */
/*   Updated: 2024/03/20 07:18:10 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_str(char **str)
{
	if (*str)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_ptr(void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

void free_img(t_image *img, void *mlx)
{
	if(!img)
		return ;
	
	if(img->img_ptr)
		mlx_destroy_image(mlx, img->img_ptr);
 	free(img);
	img = NULL;
}

void free_minimap(t_minimap *minimap, t_data *data)
{
	if(!minimap)
		return ;
	free_img(minimap->base, data->mlx);
	free_img(minimap->resize, data->mlx);
	free_img(minimap->small, data->mlx);
	free_img(minimap->wall, data->mlx);
	free_img(minimap->ground, data->mlx);
	free_img(minimap->player, data->mlx);
	free_img(minimap->player_rot, data->mlx);
	free_img(minimap->exit, data->mlx);
	free(minimap);
}

void	free_cub(t_texture *cub, t_data *data)
{
	if (!cub)
		return ;
	free_minimap(cub->minimap, data);
	free_img(cub->base_img, data->mlx);
	free_img(cub->img1, data->mlx);
	free_img(cub->img2, data->mlx);
	free_img(cub->no, data->mlx);
	free_img(cub->so, data->mlx);
	free_img(cub->ea, data->mlx);
	free_img(cub->we, data->mlx);
	free_str(&cub->no_path);
	free_str(&cub->so_path);
	free_str(&cub->we_path);
	free_str(&cub->ea_path);
	free_str(&cub->map_str);
	free(cub);
}

void	free_grid(int ***grid, int max_row)
{
	int	i;

	i = 0;
	if ((*grid))
	{
		while (i < max_row)
			free((*grid)[i++]);
		free((*grid));
		*grid = NULL;
	}
}

void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_grid(&map->grid, map->row_max);
	free(map);
}

void	free_data(t_data *data)
{
	free_cub(data->texture, data);
	free_map(data->map);
	if (data->player)
		free(data->player);
	if (data->mlx_win)
	{
		mlx_destroy_window(data->mlx, data->mlx_win);
		mlx_destroy_display(data->mlx);
	}
	if (data->mlx)
		free(data->mlx);
}