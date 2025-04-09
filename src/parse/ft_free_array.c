/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 18:38:14 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/07 18:39:29 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_free_array(char **array)
{
	int	a;

	a = 0;
	if (!array)
		return ;
	while (array[a] != NULL)
	{
		free(array[a]);
		a++;
	}
	free(array);
}