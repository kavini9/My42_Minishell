/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 19:32:39 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 20:43:46 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int			len_ndl;
	const char	*occ;

	if (*needle == '\0' )
		return ((char *) haystack);
	while (*haystack != '\0' && (int) len--)
	{
		len_ndl = (int) len + 1;
		occ = haystack;
		while (*needle != '\0' && *occ == *needle && len_ndl--)
		{
			occ++;
			needle++;
		}
		if (*needle == '\0')
			return ((char *) haystack);
		needle -= (occ - haystack++);
	}
	return (0);
}
/******************************************************************************/
/*                                                                            */
/*DESCRIPTION                                                                 */
/*   Strnstr locates the first occurrence of the null-terminated string       */
/*	 needle in the string haystack, where not more than len characters are    */
/*	 searched.  Characters that appear after a `\0' character are not         */
/*	 searched.                                                                */
/*                                                                            */
/*RETURN VALUES                                                               */
/*   If needle is an empty string, haystack is returned; if needle occurs     */
/*	 nowhere in haystack, NULL is returned; otherwise a pointer to the first  */
/*	 character of the first occurrence of needle is returned.                 */
/*                                                                            */
/******************************************************************************/
