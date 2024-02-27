/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:08:36 by yubi42            #+#    #+#             */
/*   Updated: 2024/02/27 13:36:58 by hstein           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	setup_found(t_texture_ok setup_vars)
{
	if (setup_vars.no == FALSE || setup_vars.so == FALSE)
		return (FALSE);
	if (setup_vars.ea == FALSE || setup_vars.we == FALSE)
		return (FALSE);
	if (setup_vars.c == FALSE || setup_vars.f == FALSE)
		return (FALSE);
	return (TRUE);
}

void	setup_vars_check(t_texture *cub, t_read *reading, t_texture_ok *setup_vars,
		char (*err)[50])
{
	while (reading->bytes > 0 && !setup_found(*setup_vars))
	{
		if (reading->buf == '\n')
		{
			if (!line_valid(reading, cub, setup_vars, err))
				break ;
			if (reading->str)
				free(reading->str);
			reading->str = NULL;
			reading->i = 0;
		}
		else
		{
			reading->str = ft_realloc(reading->str, reading->i + 2);
			if (malloc_err(reading->str, &reading->return_value, err))
				break ;
			reading->str[reading->i++] = reading->buf;
			reading->str[reading->i] = '\0';
		}
		reading->bytes = read(reading->fd, &reading->buf, 1);
	}
}

void	setup_map_str(t_texture *cub, t_read *reading, char (*err)[50])
{
	reading->i = 0;
	while (reading->bytes > 0 && reading->buf == '\n')
		reading->bytes = read(reading->fd, &reading->buf, 1);
	while (reading->bytes > 0)
	{
		cub->map_str = ft_realloc(cub->map_str, reading->i + 2);
		if (malloc_err(cub->map_str, &reading->return_value, err))
			break ;
		cub->map_str[reading->i] = reading->buf;
		cub->map_str[reading->i + 1] = '\0';
		reading->bytes = read(reading->fd, &reading->buf, 1);
		if (reading->buf == '\n' && cub->map_str[reading->i] == '\n')
		{
			ft_strlcpy(*err, "Forbidden newline in map",
				ft_strlen("Forbidden newline in map") + 1);
			reading->return_value = FALSE;
			break ;
		}
		reading->i++;
	}
}
