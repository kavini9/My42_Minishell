/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 23:10:27 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 20:02:50 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*tmp_dst;

	tmp_dst = (char *) dst;
	if (src < dst)
	{
		tmp_dst += len - 1;
		src += len - 1;
		while (len--)
		{
			*tmp_dst-- = *(char *)src--;
		}
	}
	else if (src != dst)
	{
		while (len--)
		{
			*tmp_dst++ = *(char *)src++;
		}
	}
	return (dst);
}
/******************************************************************************/
/*                                                                            */
/*DESCRIPTION                                                                 */
/*     Memmove copies len bytes from string src to string dst.                */
/*     The two strings may overlap; the copy is always done in a              */
/*     non-destructive manner.                                                */
/*                                                                            */
/*RETURN VALUES                                                               */
/*     Memmove returns the original value of dst.                             */
/*                                                                            */
/*FUNCTION EXECUTION                                                          */
/*     Overlap Handling: If the memory address of the source is before that of*/
/*     the destination, there's a possibility of overlap.                     */
/*                                                                            */
/*     If src < dst, the copying is done from right to left to ensure later   */
/*     parts of src aren't changed before being copied.                       */
/*     If src and dst point to the same memory location, nothing is changed.  */
/*     Otherwise, copying progresses forward from left to right.              */
/*                                                                            */
/******************************************************************************/
