/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_run.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:32:56 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/18 16:48:51 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	msh_init(t_msh *msh, char **envp)
{
	ft_memset(msh, 0, sizeof(t_msh));
	msh -> cwd = getcwd(NULL, 0);
	if (!msh -> cwd)
		msh_error(msh, (ERRNO | LOG | CLEAN | EXIT) << 8 | 1, CWD,
			"init");
	msh -> old_wd = ft_strdup(msh -> cwd);
	if (!msh -> old_wd)
		msh_error(msh, LOG | CLEAN | EXIT << 8 | 1, ERR_MALLOC, NULL);
	duplicate_env(msh, envp);
	set_shlvl(msh, msh -> envl);
	ft_memset(msh -> hdocfd_l, -1, sizeof(int) * 16);
}

void	msh_execute(t_msh *msh)
{
	here_doc(msh, msh -> cmd, msh -> hdocfd_l, 0);
	if (msh -> exit_code != 130)
	{
		if (msh -> cmd_count == 1 && is_builtin((*msh->cmd)-> cmd))
			execin_shell(msh, *msh -> cmd);
		else
		{
			execin_child(msh, msh -> cmd, -1, 0);
		}
	}
	reset_cmd_attr(msh);
}

void	msh_parse(t_msh *msh, char *line)
{
	t_parse	aux;

	ft_memset(&aux, 0, sizeof(t_parse));
	msh -> aux = &aux;
	init_parse_structs(msh, line);
	line_split_bypipe(msh, line, line, msh -> aux -> seg);
	seg_tokenize(msh, msh -> aux);
	expand_tokens(msh, msh -> aux -> token);
	init_cmd_struct(msh, msh -> cmd_count);
	setup_cmd(msh, msh -> aux -> token, msh -> cmd);
	clean_aux(msh, msh -> aux);
}

int	msh_exit(t_msh *msh, char *line)
{
	if (!line)
	{
		printf("exit\n");
		msh_clean(msh);
		return (1);
	}
	return (0);
}

void	msh_loop(t_msh *msh)
{
	char	*line;

	while (1)
	{
		if (isatty(fileno(stdin)))
			init_sig();
		line = readline("minishell> ");
		if (msh_exit(msh, line))
			exit(msh->exit_code);
		if (g_sig == SIGINT)
		{
			msh->exit_code = 130;
			g_sig = 0;
		}
		add_history(line);
		if (*line && !msh_validate_line(msh, &line))
		{
			msh_parse(msh, line);
			msh->exit_code = 0;
			msh_execute(msh);
		}
		else if (line)
			free(line);
	}
	rl_clear_history();
}
