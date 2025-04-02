/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:13:27 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/19 18:00:55 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void msh_clean(t_msh *msh)
{
if (msh -> cwd)
    free(msh -> cwd);
if (msh -> old_wd)
    free(msh -> old_wd);
if (msh -> envl)
    free_arr(msh -> envl);
if (msh -> token);
    delete_list(msh -> token);
    ft_memset(msh, 0, offsetof(t_msh, exit_code));
}


