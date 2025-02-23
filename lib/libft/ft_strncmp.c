/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 22:30:42 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 20:20:42 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 != '\0' || *s2 != '\0') && n--)
	{
		if (*(unsigned char *) s1 != *(unsigned char *) s2)
			return (*(unsigned char *) s1 - *(unsigned char *) s2);
		s1++;
		s2++;
	}
	return (0);
}
/******************************************************************************/
/*                                                                            */
/*DESCRIPTION                                                                 */
/*   Strncmp lexicographically compare the null-terminated strings s1 and s2  */
/*	 not more than n characters.  Because strncmp is designed for comparing   */
/*	 strings rather than binary data, characters that appear after a `\0'     */
/*	 character are not compared.                                              */
/*                                                                            */
/*RETURN VALUES                                                               */
/*   Strncmp returns an integer greater than, equal to, or less than 0,       */
/*	 according as the string s1 is greater than, equal to, or less than the   */
/*	 string s2.  The comparison is done using unsigned characters, so that    */
/*	 `\200' is greater than `\0'.                                             */
/*                                                                            */
/******************************************************************************/
