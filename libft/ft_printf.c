/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacorrei <gacorrei@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:32:41 by gacorrei          #+#    #+#             */
/*   Updated: 2023/02/01 09:01:55 by gacorrei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putstr_special(char *str)
{
	int	c;

	if (!str)
		return (write(1, "(null)", 6));
	c = 0;
	while (str[c])
		write(1, &str[c++], 1);
	return (c);
}

static int	ft_p(unsigned long n, char *base, unsigned int len, int flag)
{
	int	ct;

	if (!n)
		return (write(1, "(nil)", 5));
	ct = 0;
	if (flag == 0)
		ct += write (1, "0x", 2);
	if (n >= len)
		ct += ft_p(n / len, base, len, 1);
	ct += write(1, &base[n % len], 1);
	return (ct);
}

static int	ft_pbase(long long n, char *base, unsigned int len)
{
	int	ct;

	ct = 0;
	if (n < 0)
	{
		ct += write(1, "-", 1);
		n = n * -1;
	}
	if (n >= len)
		ct += ft_pbase(n / len, base, len);
	ct += write(1, &base[n % len], 1);
	return (ct);
}

static int	ft_output(char c, va_list param, int t)
{
	if (c == 'c')
	{
		t = va_arg(param, int);
		return (write(1, &t, 1));
	}
	else if (c == '%')
		return (write(1, "%", 1));
	else if (c == 's')
		return (ft_putstr_special(va_arg(param, char *)));
	else if (c == 'd' || c == 'i')
		return (ft_pbase(va_arg(param, int), "0123456789", 10));
	else if (c == 'u')
		return (ft_pbase(va_arg(param, unsigned int), "0123456789", 10));
	else if (c == 'p')
		return (ft_p(va_arg(param, unsigned long), "0123456789abcdef", 16, 0));
	else if (c == 'x')
		return (ft_pbase(va_arg(param, unsigned int), "0123456789abcdef", 16));
	else if (c == 'X')
		return (ft_pbase(va_arg(param, unsigned int), "0123456789ABCDEF", 16));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		ct;
	va_list	param;

	va_start(param, str);
	i = 0;
	ct = 0;
	while (str[i])
	{
		if (str[i] != '%')
			ct += write(1, &str[i], 1);
		else
		{
			i++;
			ct += ft_output(str[i], param, ct);
		}
		i++;
	}
	va_end(param);
	return (ct);
}
