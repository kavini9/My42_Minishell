/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 20:57:11 by wweerasi          #+#    #+#             */
/*   Updated: 2025/05/11 21:11:11 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*tmp;

	if (size > UINT_MAX)
		return (NULL);
	tmp = malloc(size);
	if (ptr != NULL)
		ft_bzero(ptr, count * size);
	return (ptr);
}