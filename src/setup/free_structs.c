/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:50:16 by yubi42            #+#    #+#             */
/*   Updated: 2024/02/26 15:37:28 by yubi42           ###   ########.fr       */
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

void	free_cub(t_cub *cub)
{
	free_str(&cub->no);
	free_str(&cub->so);
	free_str(&cub->we);
	free_str(&cub->ea);
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