/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:56:55 by jborner           #+#    #+#             */
/*   Updated: 2023/05/22 12:18:18 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_rows(char const *s, char c)
{
	int		count;

	count = 0;
	while (*s)
	{
		if (*s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
		else
			s++;
	}
	return (count);
}

static int	free_array(char **array, int i)
{
	if (array[i] == NULL)
	{
		while (i > 0)
			free(array[--i]);
		free(array);
		return (0);
	}
	return (1);
}

static char	**fill_array(char const *s, char c, char **array)
{
	int	len;
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len = 0;
			while (*s && *s != c)
			{
				len++;
				s++;
			}
			array[i] = ft_substr(s - len, 0, len);
			if (!free_array(array, i))
				return (NULL);
			i++;
		}
		else
			s++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **)malloc(sizeof(char *) * (count_rows(s, c) + 1));
	if (!array)
		return (NULL);
	array = fill_array(s, c, array);
	return (array);
}
