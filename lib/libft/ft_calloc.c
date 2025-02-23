/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 23:27:29 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/08 21:34:31 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (size != 0 && count > UINT_MAX / size)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr != NULL)
		ft_bzero(ptr, count * size);
	return (ptr);
}
/******************************************************************************/
/*                                                                            */
/*DESCRIPTION                                                                 */
/*    Calloc contiguously allocates enough space for count objects that are   */
/*    size bytes of memory each and returns a pointer to the allocated memory.*/
/*    The allocated memory is filled with bytes of value zero.                */
/*                                                                            */
/*RETURN VALUES                                                               */
/*    Calloc return a pointer to allocated memory.  If there is an error,     */
/*    it returns a NULL pointer.                                              */
/*                                                                            */
/******************************************************************************/
