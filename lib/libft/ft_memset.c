/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 14:50:59 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 18:39:51 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*temp_b;

	temp_b = (unsigned char *) b;
	while (len > 0)
	{
		*temp_b = (unsigned char) c;
		temp_b++;
		len--;
	}
	return (b);
}
/******************************************************************************/
/*                                                                            */
/*DESCRIPTION                                                                 */
/*	 The memset writes len bytes of value c (converted to an unsigned char)   */
/*   to the string b.                                                         */
/*                                                                            */
/*RETURN VALUES                                                               */
/*   The memset() function returns its first argument.                        */
/*                                                                            */
/******************************************************************************/
