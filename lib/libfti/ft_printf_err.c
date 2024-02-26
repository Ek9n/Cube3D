/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yubi42 <yubi42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:09:55 by jborner           #+#    #+#             */
/*   Updated: 2024/02/25 15:49:26 by yubi42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	check_type_err(char c, va_list list, int *count)
{
	if (c == 'c')
		ft_putchar_err((char)va_arg(list, int), count);
	if (c == 's')
		ft_putstr_err(va_arg(list, char *), count);
	if (c == 'p')
		ft_putpoint_err((unsigned long)va_arg(list, unsigned long), count);
	if (c == 'd' || c == 'i')
		ft_putnbr_err(va_arg(list, int), count);
	if (c == 'u')
		ft_putnbr_err(va_arg(list, unsigned int), count);
	if (c == 'x')
		ft_puthex_err(va_arg(list, unsigned int), 'a', count);
	if (c == 'X')
		ft_puthex_err(va_arg(list, unsigned int), 'A', count);
	if (c == '%')
		ft_putchar_err(c, count);
}

int	ft_printf_err(const char *str, ...)
{
	va_list	list;
	int		count;

	va_start(list, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			check_type_err(*str++, list, &count);
		}
		else
			ft_putchar_err(*str++, &count);
	}
	va_end(list);
	return (count);
}
