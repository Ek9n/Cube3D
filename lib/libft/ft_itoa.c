/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jborner <jborner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:29:12 by jborner           #+#    #+#             */
/*   Updated: 2023/05/22 13:12:17 by jborner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_bytes(long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	if (n > 9)
		count += count_bytes(n / 10);
	count++;
	return (count);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		count;
	long	num;

	num = n;
	count = count_bytes(num);
	str = (char *)malloc(sizeof(char) * count + 1);
	if (!str)
		return (NULL);
	if (num < 0)
	{
		str[0] = '-';
		num = -num;
	}
	str[count] = '\0';
	count--;
	if (num == 0)
		str[count] = 0 + '0';
	while (num)
	{
		str[count] = (num % 10) + '0';
		num /= 10;
		count--;
	}
	return (str);
}
