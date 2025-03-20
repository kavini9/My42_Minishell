/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putnbr_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:49:53 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/19 16:09:20 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf_fd.h"

void	putnbr_fd(int nbr, t_base b, int *totlen, int fd)
{
	long int	n;

	n = nbr;
	if (n < 0)
	{
		putchar_fd('-', totlen, fd);
		n = -n;
	}
	if (n >= b.base)
		putnbr_fd(n / b.base, b, totlen, fd);
	if (*totlen != -1)
		putchar_fd(b.str[n % b.base], totlen, fd);
	else
		return ;
}
