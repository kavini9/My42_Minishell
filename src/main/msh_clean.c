/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_clean.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:13:27 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/25 23:59:25 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    free_cmd()
void msh_clean(t_msh *msh)
{
if (msh -> cwd)
    free(msh -> cwd);
if (msh -> old_wd)
    free(msh -> old_wd);
if (msh -> envl)
    free_arr(msh -> envl);
if (msh -> cmd);
    free_cmd(msh -> cmd);
ft_memset(msh, 0, offsetof(t_msh, exit_code));
}
