/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:49:20 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 20:12:01 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	slen;

	slen = (int) ft_strlen(s);
	s += slen;
	while (slen-- >= 0)
	{
		if (*s == (char) c)
			return ((char *) s);
		s--;
	}
	return (0);
}
/******************************************************************************/
/*                                                                            */
/*DESCRIPTION                                                                 */
/*     Strrchr locates the last occurrence of c (converted to a char) in the  */
/*     string pointed to by s. The terminating null character is considered   */
/*     to be part of the string; therefore if c is `\0', function locates the */
/*     terminating `\0'.                                                      */
/*                                                                            */
/*RETURN VALUES                                                               */
/*     Strrchr return a pointer to the located character, or NULL if the      */
/*     character does not appear in the string.                               */
/*                                                                            */
/******************************************************************************/
