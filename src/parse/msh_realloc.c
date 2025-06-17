/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_realloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 15:39:22 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/17 05:12:32 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*free_vtype(void *ptr, t_vtype type)
{
	if (type == REG)
		free(ptr);
	else if (type == ARR)
		free_arr((void **) ptr);
	else if (type == TOK)
		free_token((t_token *) ptr);
	else if (type == RED)
		free_redir((t_redir **) ptr);
	return (NULL);
}

static size_t	get_sizeof(t_vtype type)
{
	if (type == REG)
		return (sizeof(char));
	else if (type == ARR)
		return (sizeof(void *));
	else if (type == TOK)
		return (sizeof(t_token));
	else if (type == RED)
		return (sizeof(t_redir *));
	return (sizeof(char));
}

void	*msh_realloc(void *ptr, size_t len_prev, size_t len_new, t_vtype type)
{
	void	*ptr_new;
	size_t	size;

	size = get_sizeof(type);
	if (!ptr)
		return (ft_calloc(len_new, size));
	if (!len_new)
		return (free_vtype(ptr, type));
	ptr_new = ft_calloc(len_new, size);
	if (!ptr_new)
		return (free_vtype(ptr, type));
	if (len_prev > 0)
	{
		if (len_prev > len_new)
			ft_memcpy(ptr_new, ptr, len_new * size);
		else
			ft_memcpy(ptr_new, ptr, len_prev * size);
	}
	free(ptr);
	return (ptr_new);
}
