/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:03:58 by yubi42            #+#    #+#             */
/*   Updated: 2024/02/27 14:55:01 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	malloc_err(void *ptr, int *return_value, char (*err)[50])
{
	if (!ptr)
	{
		ft_strlcpy(*err, "Not enough memory", ft_strlen("Not enough memory")
			+ 1);
		if (return_value != NULL)
			*return_value = FALSE;
		return (TRUE);
	}
	return (FALSE);
}

void destroy_images(t_data *data)
{
	if (data->texture->no_addr)
		mlx_destroy_image(data->mlx, data->texture->no_addr);
	if (data->texture->so_addr)
		mlx_destroy_image(data->mlx, data->texture->so_addr);
	if (data->texture->we_addr)
		mlx_destroy_image(data->mlx, data->texture->we_addr);
	if (data->texture->ea_addr)
		mlx_destroy_image(data->mlx, data->texture->ea_addr);
}

void	close_game(t_data *data, char *msg)
{
	destroy_images(data);
	free_data(data);
	if (!msg)
		exit(EXIT_SUCCESS);
	ft_printf_err(msg);
	exit(EXIT_FAILURE);
}
