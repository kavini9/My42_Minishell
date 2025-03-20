/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 20:58:42 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/19 20:01:35 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fd.h"

static t_base	ft_base(char *str_b)
{
	t_base	base;

	base.str = str_b;
	base.base = ft_strlen(str_b);
	return (base);
}

static void	ft_cspdiuxx(const char *spec, va_list args, int *totlen, int fd)
{
	if (*spec == 'c')
		putchar_fd(va_arg(args, int), totlen, fd);
	else if (*spec == 's')
		putstr_fd(va_arg(args, char *), totlen, fd);
	else if (*spec == 'p')
	{
		putstr_fd("0x", totlen, fd);
		putnbr_u_fd(va_arg(args, unsigned long), ft_base(HEX), totlen, fd);
	}
	else if (*spec == 'd' || *spec == 'i')
		putnbr_fd(va_arg(args, int), ft_base(DEC), totlen, fd);
	else if (*spec == 'u')
		putnbr_u_fd(va_arg(args, unsigned int), ft_base(DEC), totlen, fd);
	else if (*spec == 'x')
		putnbr_u_fd(va_arg(args, unsigned int), ft_base(HEX), totlen, fd);
	else if (*spec == 'X')
		putnbr_u_fd(va_arg(args, unsigned int), ft_base(HEX_U), totlen, fd);
	else if (*spec == '%')
		putchar_fd('%', totlen, fd);
	else
		putchar_fd(*spec, totlen, fd);
}

int	printf_fd(int fd, const char *format, ...)
{
	va_list	args;
	int		totlen;

	totlen = 0;
	va_start(args, format);
	while (*format && totlen != -1)
	{
		if (*format == '%' && format++ && *format)
			ft_cspdiuxx(format, args, &totlen, fd);
		else if (*format)
			putchar_fd(*format, &totlen, fd);
		if (*format)
			format++;
	}
	va_end(args);
	return (totlen);
}
