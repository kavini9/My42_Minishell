/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:32:56 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/18 09:25:09 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


void msh_init(t_msh *msh, char **envp)
{
	ft_memset(msh, 0, sizeof(t_msh));
	msh -> cwd = getcwd(NULL, 0);
	if (!msh -> cwd)
		msh_error(msh, (ERRNO|LOG|CLEAN|EXIT) << 8 | 1, ERR_GETCWD, "init");
	msh -> old_wd = ft_strdup(msh -> cwd);//if we go one level up the old pwd is different
	if (!msh -> old_wd)
		msh_error(msh, LOG|CLEAN|EXIT << 8 | 1 , ERR_MALLOC, NULL);//"minishell: fatal error: memory allocation failed in %s.\n"
	duplicate_env(msh, envp);
	set_shlvl(msh, msh -> envl);
	ft_memset(msh -> hdocfd_l, -1, sizeof(int) * 16);
}

void    msh_execute(t_msh *msh)
{
	here_doc(msh, msh -> cmd, msh -> hdocfd_l, 0);//what kind of errors can occur with this? pipe open, read and write to pipe
	if (msh -> exit_code != 130)
	{
		if (msh -> cmd_count == 1 && is_builtin((*msh->cmd) -> cmd))//TODO: see the dereference here. see if it needs too be chnged in struct.
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
	//print_tokens(msh -> aux -> token);// remove later
    expand_tokens(msh, msh -> aux -> token);
	//print_expand_arrays(msh -> aux -> token);// remove later
	init_cmd_struct(msh, msh -> cmd_count);
	setup_cmd(msh, msh -> aux -> token, msh -> cmd);
	//print_cmd_members(msh -> cmd);// remove later
	clean_aux(msh, msh -> aux);
}

// void	msh_exit(t_msh *msh)
// {
// 	printf("exit\n");
// 	msh_clean(msh);
// 	exit(msh->exit_code);
// }

// char	*msh_read_line(void)
// {
// 	char	*line;
// 	char	*trimmed;

// 	if (isatty(fileno(stdin)))
// 		return readline("minishell> ");
// 	line = get_next_line(fileno(stdin));
// 	if (!line)
// 		return NULL;
// 	trimmed = ft_strtrim(line, "\n");
// 	free(line);
// 	return trimmed;
// }

// void	msh_loop(t_msh *msh)
// {
// 	char	*line;

// 	while (1)
// 	{
// 		if (isatty(fileno(stdin)))
// 			init_sig();
// 		line = msh_read_line();
// 		if (!line)//check if we can replace msh_exit
// 			msh_exit(msh);
// 		if (g_sig == SIGINT)
// 		{
// 			msh->exit_code = 130;
// 			g_sig = 0;
// 		}
// 		add_history(line);
// 		if (*line && !msh_validate_line(msh, &line))
// 		{
// 			msh_parse(msh, line);
// 			msh->exit_code = 0;
// 			msh_execute(msh);
// 		}
// 		//free(line);
// 	}
// 	rl_clear_history();
// }

void	msh_loop(t_msh *msh)
{
	char	*line;
	
	while(1)
	{
		if (isatty(fileno(stdin)))
            init_sig();
		//line = readline("minishell> ");
		if (isatty(fileno(stdin)))
			line = readline("minishell> "); // use custom prompt string
		else
		{
			line = get_next_line(fileno(stdin)); // tester gives input
			if (!line)
				break; // avoid ft_strtrim(NULL) segfault
			char *trimmed = ft_strtrim(line, "\n"); // remove newline
			free(line);
			line = trimmed;
		}
		if (!line) // Handle Ctrl+D (EOF)
		{
			printf("exit\n");
			msh_clean(msh);
			exit(msh->exit_code);
		}
		if (g_sig == SIGINT)
		{
			msh->exit_code = 130;
			g_sig = 0;
		}
		add_history(line);
		if (*line && !msh_validate_line(msh, &line))
		{
			msh_parse(msh, line);
			msh->exit_code = 0; //Placeholder — replace later
			msh_execute(msh);
		}
		else if (line)
		 	free(line);
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **envp)
{
	t_msh	msh;
	(void) av;
	
	if (ac != 1)
		exit(printf("# minishell: Error: Invalid number of arguments."
		"\n# Usage: ./minishell"));
	msh_init(&msh, envp);
	msh_loop(&msh);
	msh_clean(&msh);
	exit(msh.exit_code);
}
 
//	print_envl(&msh);
/*
void	msh_parse(t_msh *msh, char *line)
{
	t_parse	aux;//in static memory remember to assign to cmd struct before leaving this function.

	msh -> aux = &aux;
	init_parse_structs(msh, line);
	line_split_bypipe(msh, line, msh -> aux -> seg);
    print_segments(msh -> aux -> seg);//debugging purpose
	seg_tokenize(msh, msh -> aux);
    print_tokens(msh -> aux -> token);//debugging purpose
    expand_tokens(msh, msh -> aux -> token);
	print_expand_arrays(msh -> aux -> token);//debugging purpose
	init_cmd_struct(msh, msh -> cmd_count);
	setup_cmd(msh, msh -> aux -> token, msh -> cmd);
	print_cmd_members(msh -> cmd);//debugging purpose
	clean_aux(msh, msh -> aux);
}
*/