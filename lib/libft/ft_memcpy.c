/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 18:17:48 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 19:59:58 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*tmp_dst;

	tmp_dst = (char *) dst;
	if (dst != NULL || src != NULL)
	{
		while (n--)
			*tmp_dst++ = *(const char *)src++;
	}
	return (dst);
}
/******************************************************************************/
/*                                                                            */
/*DESCRIPTION                                                                 */
/*   Memcpy copies n bytes from memory area src to memory area dst.           */
/*   If dst and src overlap, behavior is undefined.                           */
/*                                                                            */
/*RETURN VALUES                                                               */
/*   Memcpy returns the original value of dst.                                */
/*                                                                            */
/******************************************************************************/
