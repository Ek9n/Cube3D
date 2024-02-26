/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_err.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 12:45:11 by jborner           #+#    #+#             */
/*   Updated: 2024/02/25 15:49:23 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_err(char c, int *count)
{
	if (write(2, &c, 1) < 0)
		return ;
	(*count)++;
}

void	ft_putstr_err(char *s, int *count)
{
	if (!s)
	{
		ft_putstr_err("(null)", count);
		return ;
	}
	while (*s)
		ft_putchar_err(*s++, count);
}

void	ft_putnbr_err(long num, int *count)
{
	if (num < 0)
	{
		ft_putchar_err('-', count);
		num *= -1;
	}
	if (num > 9)
		ft_putnbr_err(num / 10, count);
	ft_putchar_err((char){num % 10 + '0'}, count);
}

void	ft_puthex_err(unsigned long num, char c, int *count)
{
	char	digit;

	if (num > 15)
		ft_puthex_err((num / 16), c, count);
	digit = num % 16;
	if (digit < 10)
		digit += '0';
	else
		digit += c - 10;
	ft_putchar_err(digit, count);
}

void	ft_putpoint_err(unsigned long num, int *count)
{
	if (num == 0)
	{
		ft_putstr_err("(nil)", count);
		return ;
	}
	ft_putchar_err('0', count);
	ft_putchar_err('x', count);
	ft_puthex_err(num, 'a', count);
}
