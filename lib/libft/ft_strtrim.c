/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 18:09:37 by jborner           #+#    #+#             */
/*   Updated: 2023/05/22 12:19:17 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static int	array_len(char const *s1, char const *set)
{
	int	start;
	int	end;

	start = 0;
	end = ft_strlen(s1) - 1;
	while (is_set(s1[start++], set))
		if (!s1[start])
			return (0);
	while (end >= start && is_set(s1[end], set))
		end--;
	return (end - start + 2);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str_trim;
	int		total_len;
	int		start;

	if (s1 == NULL || set == NULL)
		return (NULL);
	total_len = array_len(s1, set);
	if (s1[0] == '\0' || total_len == 0)
	{
		str_trim = (char *)malloc(sizeof(char) * 1);
		str_trim[0] = '\0';
		return (str_trim);
	}
	str_trim = (char *)malloc(sizeof(char) * total_len + 1);
	if (str_trim != NULL)
	{
		start = 0;
		while (is_set(s1[start], set))
			start++;
		ft_strlcpy(str_trim, &s1[start], total_len + 1);
		return (str_trim);
	}
	return (NULL);
}
