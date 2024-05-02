/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:50:16 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/02 17:11:48 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	free_minimap(t_minimap *minimap, t_data *data)
{
	if (!minimap)
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

void	free_texture(t_texture *texture, t_data *data)
{
	if (!texture)
		return ;
	free_minimap(texture->minimap, data);
	free_img(texture->base_img, data->mlx);
	free_img(texture->carframe, data->mlx);
	free_img(texture->carframe2, data->mlx);
	free_img(texture->steeringwheel, data->mlx);
	free_img(texture->steeringwheel2, data->mlx);
	free_img(texture->num0, data->mlx);
	free_img(texture->num1, data->mlx);
	free_img(texture->num2, data->mlx);
	free_img(texture->num3, data->mlx);
	free_img(texture->num4, data->mlx);
	free_img(texture->num5, data->mlx);
	free_img(texture->num6, data->mlx);
	free_img(texture->num7, data->mlx);
	free_img(texture->num8, data->mlx);
	free_img(texture->num9, data->mlx);
	free_img(texture->slash, data->mlx);
	free_img(texture->kmh, data->mlx);
	free_img(texture->game_over, data->mlx);
	free_img(texture->img1, data->mlx);
	free_img(texture->img2, data->mlx);
	free_img(texture->black, data->mlx);
	free_img(texture->transparent, data->mlx);
	free_img(texture->goal, data->mlx);
	free_img(texture->no, data->mlx);
	free_img(texture->so, data->mlx);
	free_img(texture->ea, data->mlx);
	free_img(texture->we, data->mlx);
	free_str(&texture->no_path);
	free_str(&texture->so_path);
	free_str(&texture->we_path);
	free_str(&texture->ea_path);
	free_str(&texture->map_str);
	free(texture);
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
	free_texture(data->texture, data);
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
