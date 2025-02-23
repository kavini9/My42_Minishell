/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:34:10 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/08 21:35:40 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_intlen(int n)
{
	int	len_int;

	len_int = 0;
	if (n == -2147483648)
	{
		len_int += 2;
		n = 147483648;
	}
	else if (n < 0)
	{
		len_int += 1;
		n = -1 * n;
	}
	while (n >= 10)
	{
		n /= 10;
		len_int++;
	}
	return (len_int + 1);
}

static void	ft_putnbr(char *itoa, int nb)
{
	if (nb >= 10)
	{
		ft_putnbr(itoa - 1, nb / 10);
		ft_putnbr(itoa, nb % 10);
	}
	else
		*itoa = (nb + '0');
}

char	*ft_itoa(int n)
{
	char	*itoa;
	int		intlen;
	char	*start;

	intlen = ft_intlen(n);
	itoa = malloc((intlen + 1) * sizeof(char));
	start = itoa;
	if (itoa != NULL)
	{
		if (n < 0)
		{
			*itoa++ = '-';
			intlen--;
			if (n == -2147483648)
			{
				*itoa++ = '2';
				intlen--;
				n = -147483648;
			}
			n = -1 * n;
		}
		ft_putnbr(itoa + intlen - 1, n);
		*(itoa + intlen) = '\0';
	}
	return (start);
}
