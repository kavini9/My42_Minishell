/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:09:14 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 20:28:16 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	while (n--)
	{
		if (*(unsigned char *)s == (unsigned char)c)
			return ((void *)s);
		s++;
	}
	return (NULL);
}
/******************************************************************************/
/*                                                                            */
/*DESCRIPTION                                                                 */
/*    Memchr locates the first occurrence of c (converted to an unsigned      */
/*    char) in string s.                                                      */
/*                                                                            */
/*RETURN VALUES                                                               */
/*    Memchr returns a pointer to the byte located, or NULL if no such byte   */
/*    exists within n bytes.                                                  */
/*                                                                            */
/******************************************************************************/
