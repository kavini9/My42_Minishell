/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 14:44:51 by wweerasi          #+#    #+#             */
/*   Updated: 2024/05/04 22:11:45 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lst_new;
	t_list	*node_new;
	void	*cont;

	if (lst == NULL)
		return (NULL);
	lst_new = NULL;
	while (lst != NULL)
	{
		if (f != NULL)
			cont = f(lst -> content);
		else
			cont = lst -> content;
		node_new = ft_lstnew(cont);
		if (node_new == NULL)
		{
			del(cont);
			ft_lstclear(&lst_new, del);
			return (NULL);
		}
		ft_lstadd_back(&lst_new, node_new);
		lst = lst -> next;
	}
	return (lst_new);
}
