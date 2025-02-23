/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 18:51:54 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 21:13:12 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *) s1 != *(unsigned char *) s2)
			return (*(unsigned char *) s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}
/******************************************************************************/
/*                                                                            */
/*DESCRIPTION                                                                 */
/*    Memcmp compares byte string s1 against byte string s2.  Both strings    */
/*    are assumed to be n bytes long.                                         */
/*                                                                            */
/*RETURN VALUES                                                               */
/*   Memcmp returns zero if the two strings are identical, otherwise returns  */
/*	 the difference between the first two differing bytes (treated as         */
/*	 unsigned char values, so that `\200' is greater than `\0', for example). */
/*   Zero-length strings are always identical.  This behavior is not required */
/*	 by C and portable code should only depend on the sign of the returned    */
/*	 value.                                                                   */
/*                                                                            */
/******************************************************************************/
