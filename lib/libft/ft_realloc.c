/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 15:36:58 by yubi42            #+#    #+#             */
/*   Updated: 2024/02/25 23:50:41 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *str, size_t size)
{
	void	*new_str;

	new_str = malloc(size * sizeof(char));
	if (!new_str)
		return (NULL);
	if (str != NULL)
	{
		ft_memmove(new_str, str, size - 2);
		free(str);
	}
	return (new_str);
}