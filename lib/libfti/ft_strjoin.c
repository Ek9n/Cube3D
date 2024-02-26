/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 17:40:17 by jborner           #+#    #+#             */
/*   Updated: 2023/05/17 13:44:29 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_join;
	int		s1_s;
	int		s2_s;

	s1_s = ft_strlen(s1);
	s2_s = ft_strlen(s2);
	str_join = (char *)malloc(sizeof(char) * (s1_s + s2_s + 1));
	if (str_join != NULL)
	{
		ft_memcpy(str_join, s1, s1_s);
		ft_strlcpy(&str_join[s1_s], s2, s2_s + 1);
		return (str_join);
	}
	return (NULL);
}
