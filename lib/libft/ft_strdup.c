/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 14:16:22 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 21:16:42 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;
	size_t	len;

	len = ft_strlen(s1);
	s2 = malloc(sizeof(char) * (len + 1));
	if (s2 != NULL)
	{
		while (*s1 != '\0')
		{
			*s2++ = *s1++;
		}
		*s2 = '\0';
		s2 -= len;
	}
	return (s2);
}
/******************************************************************************/
/*                                                                            */
/*DESCRIPTION                                                                 */
/*   Strdup allocates sufficient memory for a copy of the string s1, does the */
/*	 copy, and returns a pointer to it.                                       */
/*                                                                            */
/*   If insufficient memory is available, NULL is returned.                   */
/*                                                                            */
/******************************************************************************/
