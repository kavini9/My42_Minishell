/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 12:23:14 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/07 21:29:26 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_split_alloc(char const *s, char c)
{
	char	**arr_s;
	char	*temp_s;
	int		split_count;

	if (s != 0)
	{
		temp_s = (char *) s;
		split_count = 0;
		while (*temp_s != '\0')
		{
			if ((temp_s == s && *temp_s != c) \
					|| (temp_s != s && *(temp_s - 1) == c && *(temp_s) != c))
				split_count++;
			temp_s++;
		}
		arr_s = malloc((split_count + 1) * sizeof(char *));
		return (arr_s);
	}
	return (0);
}

static char	*ft_substr_alloc(char const *s, char c)
{
	char	*substr_s;
	int		substr_len;

	substr_len = 0;
	while (*s != '\0' && *s != c)
	{
		substr_len++;
		s++;
	}
	substr_s = malloc((substr_len + 1) * sizeof(char));
	return (substr_s);
}

static char	**ft_free_split(char **split, char **tmp)
{
	while (tmp-- > split)
		free (*tmp);
	free (tmp + 1);
	return (NULL);
}

static char	*ft_substr_copy(char *substr, char const *s, char c)
{
	char	*sub;

	sub = substr;
	while (*s != '\0' && *s != c)
		*sub++ = *s++;
	*sub = '\0';
	return (substr);
}

char	**ft_split(char const *s, char c)
{
	char	**split_s;
	char	*tmp_s;
	char	**tmp_split;

	tmp_s = (char *) s;
	split_s = ft_split_alloc(s, c);
	if (split_s != NULL)
	{
		tmp_split = split_s;
		while (*tmp_s != '\0')
		{
			if ((tmp_s == s && *tmp_s != c) \
					|| (tmp_s != s && *(tmp_s - 1) == c && *(tmp_s) != c))
			{
				*tmp_split = ft_substr_alloc(tmp_s, c);
				if (*tmp_split == NULL)
					return (ft_free_split(split_s, tmp_split));
				ft_substr_copy(*tmp_split, tmp_s, c);
				tmp_split++;
			}
			tmp_s++;
		}
		*tmp_split = 0;
	}
	return (split_s);
}
