/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 12:45:20 by jborner           #+#    #+#             */
/*   Updated: 2023/05/22 12:16:32 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;

	pdest = dest;
	psrc = src;
	if (dest == src)
		return (dest);
	if (dest < src)
		while (n-- > 0)
			*pdest++ = *psrc++;
	else
	{
		pdest += n - 1;
		psrc += n - 1;
		while (n--)
			*pdest-- = *psrc--;
	}
	return (dest);
}
