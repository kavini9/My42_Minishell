/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:07:01 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 20:04:49 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	srclen;

	srclen = ft_strlen(src);
	if (dstsize != 0)
	{
		while (*src != '\0' && dstsize-- > 1)
		{
			*dest++ = *src++;
		}
		*dest = '\0';
	}
	return (srclen);
}
/******************************************************************************/
/*                                                                            */
/* DESCRIPTION                                                                */
/*	 Strlcpy take the full size of the destination buffer; dstsize and copies */
/*	 up to dstsize - 1 characters from the string src to dst, guaranteeing the*/
/*	 NUL-termination of the resulting string  if dstsize is not 0.            */
/*                                                                            */
/*	 If the src and dst strings overlap, the behavior is undefined.           */
/*                                                                            */
/*RETURN VALUES                                                               */
/*	 Strlcpy returns the total length of the string it tried to create which  */
/*	 is the length of src. If the return value is >= dstsize, the output      */
/*	 string has been truncated.  It is the caller's responsibility to handle  */
/*	 this.                                                                    */
/*                                                                            */
/******************************************************************************/
