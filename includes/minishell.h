/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:42:33 by wweerasi          #+#    #+#             */
/*   Updated: 2025/03/05 22:21:43 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>

# include "../lib/libft/libft.h"
# include "../src/parse/parse.h"
# include "../src/execute/execute.h"
# include "../src/builtin/builtin.h"
# include "../src/signal/signal.h"

typedef struct s_msh
{
	char	*cwd;
	char	*old_wd;
	int	exit_code;
	t_env	envl;
	t_token	*token;
}

#endif
