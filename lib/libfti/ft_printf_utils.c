/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:45:11 by jborner           #+#    #+#             */
/*   Updated: 2024/02/25 15:49:21 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar(char c, int *count)
{
	if (write(1, &c, 1) < 0)
		return ;
	(*count)++;
}

void	ft_putstr(char *s, int *count)
{
	if (!s)
	{
		ft_putstr("(null)", count);
		return ;
	}
	while (*s)
		ft_putchar(*s++, count);
}

void	ft_putnbr(long num, int *count)
{
	if (num < 0)
	{
		ft_putchar('-', count);
		num *= -1;
	}
	if (num > 9)
		ft_putnbr(num / 10, count);
	ft_putchar((char){num % 10 + '0'}, count);
}

void	ft_puthex(unsigned long num, char c, int *count)
{
	char	digit;

	if (num > 15)
		ft_puthex((num / 16), c, count);
	digit = num % 16;
	if (digit < 10)
		digit += '0';
	else
		digit += c - 10;
	ft_putchar(digit, count);
}

void	ft_putpoint(unsigned long num, int *count)
{
	if (num == 0)
	{
		ft_putstr("(nil)", count);
		return ;
	}
	ft_putchar('0', count);
	ft_putchar('x', count);
	ft_puthex(num, 'a', count);
}
