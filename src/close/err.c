/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hstein <hstein@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:03:58 by yubi42            #+#    #+#             */
/*   Updated: 2024/05/02 17:25:45 by hstein           ###   ########.fr       */
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

void	close_game(t_data *data, char *msg)
{
	free_data(data);
	if (!msg)
		exit(EXIT_SUCCESS);
	ft_printf_err(msg);
	exit(EXIT_FAILURE);
}
