/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 20:32:49 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/15 20:33:15 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void free_cmd_list(t_cmd *cmd_list)
{
	t_cmd *tmp;

	while (cmd_list)
	{
		tmp = cmd_list->next;
		// Free nested members if needed
		free(cmd_list);
		cmd_list = tmp;
	}
}
