/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:03:58 by yubi42            #+#    #+#             */
/*   Updated: 2024/02/26 15:38:06 by yubi42           ###   ########.fr       */
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
