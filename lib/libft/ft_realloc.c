/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:57:11 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/19 15:57:42 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size_prev, size_t size_new)
{
	void	*ptr_new;

	if (!ptr)
		return (ft_calloc(size_new, 1));
	if (!size_new)
	{
		free(ptr);
		return (NULL);
	}
	ptr_new = ft_calloc(size_new, 1);
	if (!ptr_new)
	{
		free(ptr);
		return (NULL);
	}
	if (size_prev > 0)
	{
		if (size_prev > size_new)
			ft_memcpy(ptr_new, ptr, size_new);
		else
			ft_memcpy(ptr_new, ptr, size_prev);
	}
	free(ptr);
	return (ptr_new);
}
