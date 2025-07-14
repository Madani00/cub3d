/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamchart <eamchart@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:29:56 by eamchart          #+#    #+#             */
/*   Updated: 2025/02/20 13:52:26 by eamchart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	format_specifiers(va_list arg, char specifier)
{
	int	cnt;

	cnt = 0;
	if (specifier == 's')
		cnt += put_string(va_arg(arg, char *));
	else if (specifier == 'd' || specifier == 'i')
		cnt += put_nmb(va_arg(arg, int));
	return (cnt);
}

int	put_string(char *str)
{
	int	j;
	int	cnt;

	cnt = 0;
	j = 0;
	while (str[j])
	{
		write(1, &str[j], 1);
		j++;
		cnt++;
	}
	return (cnt);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	put_nmb(int n)
{
	int	cnt;

	cnt = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		cnt += ft_putchar('-');
		n *= -1;
	}
	if (n >= 10)
	{
		cnt += put_nmb(n / 10);
		cnt += ft_putchar(n % 10 + '0');
	}
	else
	{
		cnt += ft_putchar(n + '0');
	}
	return (cnt);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	va_list	arg;

	va_start(arg, format);
	if (!format)
		return (-1);
	count = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += format_specifiers(arg, *format);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(arg);
	return (count);
}
