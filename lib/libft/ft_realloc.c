/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:57:11 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/28 16:54:54 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size_prev, size_t size_new)
{
	void	*ptr_new;

	if (!ptr)
		return (malloc(size_new));
	if (!size_new)
	{
		free(ptr);
		return (NULL);
	}
	ptr_new = malloc(size_new);
	if (!ptr_new)
		return (NULL);//should I set errno to ENOMEM
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