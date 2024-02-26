/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:50:16 by yubi42            #+#    #+#             */
/*   Updated: 2024/02/26 16:48:10 by yubi42           ###   ########.fr       */
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

void	free_cub(t_cub *cub)
{
	free_str(&cub->no_path);
	free_str(&cub->so_path);
	free_str(&cub->we_path);
	free_str(&cub->ea_path);
	free_ptr(&cub->no_addr);
	free_ptr(&cub->so_addr);
	free_ptr(&cub->we_addr);
	free_ptr(&cub->ea_addr);
	free_str(&cub->map_str);
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
	if (map)
	{
		free_grid(&map->grid, map->row_max);
		free(map);
	}
}