/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:50:36 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 21:20:47 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim_s;
	int		start;
	size_t	len;

	if (!*s1)
		return (ft_strdup(""));
	start = 0;
	len = ft_strlen(s1);
	while (ft_strchr(set, *s1))
	{
		start++;
		s1++;
	}
	s1 += len - start - 1;
	while (ft_strchr(set, *s1))
	{
		len--;
		s1--;
	}
	s1 -= len - 1;
	len -= start;
	trim_s = ft_substr(s1, start, len);
	return (trim_s);
}
