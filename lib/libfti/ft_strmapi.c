/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:07:21 by jborner           #+#    #+#             */
/*   Updated: 2023/05/22 12:18:51 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	char	*request;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	request = (char *)malloc(sizeof(char) * len + 1);
	if (!request)
		return (NULL);
	request[len] = '\0';
	while (len > 0)
	{
		len--;
		request[len] = f(len, s[len]);
	}
	return (request);
}
