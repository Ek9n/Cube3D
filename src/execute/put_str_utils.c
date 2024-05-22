/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_str_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 22:15:38 by hstein            #+#    #+#             */
/*   Updated: 2024/05/22 22:17:48 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	put_letter(t_data *data, char letter, int w, int h)
{
	int	start;
	int	end;
	int	i;
	int	j;
	int	size;

	start = (letter - 65) * data->texture->alpha->height;
	end = (letter - 65) * data->texture->alpha->height + \
		data->texture->alpha->height;
	size = 2;
	i = 0;
	while (i < data->texture->alpha->height)
	{
		j = 0;
		while (j < data->texture->alpha->height)
		{
			put_pixel_img(data->texture->base_img, w + j, h + i, \
				get_pixel_img(data->texture->alpha, start + j, i));
			j++;
		}
		i++;
	}
}

void	put_str(t_data *data, char *str, int w, int h)
{
	int		i;
	char	c;

	w -= 2;
	i = -1;
	while (str[++i])
	{
		c = str[i];
		if (c >= 'a' && c <= 'z')
			c -= 32;
		else if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z'))
			c = 'X';
		put_letter(data, c, w + i * 10, h);
	}
}
