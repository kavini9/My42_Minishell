/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_cmd_attr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 05:47:21 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/18 05:48:02 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	reset_cmd_attr(t_msh *msh)
{
	if (msh -> cmd)
		free_cmd(msh -> cmd);
	msh -> cmd = NULL;
	msh -> cmd_count = 0;
	close_all_hdocfd(msh -> hdocfd_l);
}
