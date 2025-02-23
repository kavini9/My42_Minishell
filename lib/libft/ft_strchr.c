/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:25:30 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 20:12:20 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	while (1)
	{
		if (*s == (char) c)
			return ((char *) s);
		else if (*s == '\0')
			break ;
		s++;
	}
	return (0);
}
/******************************************************************************/
/*                                                                            */
/*DESCRIPTION                                                                 */
/*     Strchr locates the first occurrence of c (converted to a char) in the  */
/*     string pointed to by s. The terminating null character is considered   */
/*     to be part of the string; therefore if c is `\0', function locates the */
/*     terminating `\0'.                                                      */
/*                                                                            */
/*RETURN VALUES                                                               */
/*     Strchr return a pointer to the located character, or NULL if the       */
/*     character does not appear in the string.                               */
/*                                                                            */
/******************************************************************************/
