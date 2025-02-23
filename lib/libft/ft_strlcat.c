/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 23:50:11 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 20:08:28 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t			lendest;
	size_t			lensrc;
	unsigned int	i;

	lendest = ft_strlen(dst);
	lensrc = ft_strlen(src);
	i = 0;
	if (dstsize == 0 || (dstsize < lendest))
	{
		return (dstsize + lensrc);
	}
	while (src[i] != '\0' && (lendest + i) < dstsize - 1)
	{
		dst[lendest + i] = src[i];
		i++;
	}
	dst[lendest + i] = '\0';
	return (lendest + lensrc);
}
/******************************************************************************/
/*                                                                            */
/*DESCRIPTION                                                                 */
/*     Strlcat take the full size of the destination buffer; dstsize and      */
/*     appends string src to the end of dst. It will append at most           */
/*	   dstsize - strlen(dst) - 1 characters.  It will then NUL-terminate,     */
/*	   unless dstsize is 0 or the original dst string was longer than         */
/*     dstsize (in practice this should not happen as it means that either    */
/*     dstsize is incorrect or that dst is not a proper string).              */
/*                                                                            */
/*     If the src and dst strings overlap, the behavior is undefined.         */
/*                                                                            */
/*RETURN VALUES                                                               */
/*     Returns the total length of the string it tried to create which is the */
/*	   initial length of dst plus the length of src.                          */
/*	   If the return value is >= dstsize, the output string has been          */
/*	   trunacated. It is the caller's responsibility to handle this.          */
/*                                                                            */
/******************************************************************************/
