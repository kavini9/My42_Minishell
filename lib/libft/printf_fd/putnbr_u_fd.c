/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_u_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 16:14:58 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/19 17:39:07 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fd.h"

void	putnbr_u_fd(unsigned long n, t_base b, int *totlen, int fd)
{
	if (n >= (unsigned long) b.base)
		putnbr_u_fd(n / b.base, b, totlen, fd);
	if (*totlen != -1)
		putchar_fd(b.str[n % b.base], totlen, fd);
	else
		return ;
}
