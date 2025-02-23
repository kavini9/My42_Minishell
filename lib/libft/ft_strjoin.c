/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 19:54:13 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/06 23:26:08 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_s;
	int		len;

	len = ft_strlen(s1) + ft_strlen(s2);
	new_s = malloc((len + 1) * sizeof(char));
	if (new_s != NULL)
	{
		while (*s1 != '\0')
			*new_s++ = *s1++;
		while (*s2 != '\0')
			*new_s++ = *s2++;
		*new_s = '\0';
		new_s -= len;
	}
	return (new_s);
}
