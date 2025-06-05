/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:32:56 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/04 20:14:53 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*prompt_gen(t_msh *msh)
// {
// 	if(ft_strcmp(msh -> cwd, msh -> old_wd)
// 		msh -> prompt = prompt_update(msh -> cwd);
// 	return(msh -> prompt)
// }

void msh_init(t_msh *msh, char **envp)
{
	ft_memset(msh, 0, sizeof(t_msh)); //DES: sets everything to NULL
	msh -> cwd = getcwd(NULL, 0);
	if (!msh -> cwd)
		msh_error(msh, (ERRNO|LOG|CLEAN|EXIT) << 8 | 1, ERR_GETCWD, "init");//"minishell: cd: error retrieving current directory: getcwd: %s\n"
	msh -> old_wd = ft_strdup(msh -> cwd);//if we go one level up the old pwd is different
	if (!msh -> old_wd)
		msh_error(msh, LOG|CLEAN|EXIT << 8 | 1 , ERR_MALLOC, NULL);//"minishell: fatal error: memory allocation failed in %s.\n"
	duplicate_env(msh, envp);
	set_shlvl(msh, msh -> envl);
}

void    msh_execute(t_msh *msh)
{
	here_doc(msh, msh -> cmd, msh -> hdocfd_l, 0);//what kind of errors can occur with this? pipe open, read and write to pipe
    if (msh -> cmd_count == 1 && is_builtin((*msh->cmd) -> cmd))//TODO: see the dereference here. see if it needs too be chnged in struct.
        execin_shell(msh, *msh -> cmd);
    else
        execin_child(msh, msh -> cmd, -1, 0);
}

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
	print_expand_arrays(msh -> aux -> token);
	//init_cmd_struct(msh, msh -> cmd_count);
	//setup_cmd(*msh, msh -> aux -> token, msh -> cmd);
}

void	msh_loop(t_msh *msh)
{
	char	*line;
	
	(void) *msh;
	while(1)
	{
		if (isatty(fileno(stdin)))
            init_sig();
		line = readline("minishell> ");
		add_history(line);//brought this back to here since we are not handling unmatched quotes
		if (*line)
		{	if (msh_validate_line(msh, &line))//to add entire input to history in unclosed commands and trailing pipe case
				printf("Syntax Error\n");//write a function or this
			else 
			{
				printf("line OK: %s\n", line);
				msh_parse(msh, line);//DES: parse and tokenize and add the list of tokens to msh -> token.
				//msh_execute(msh);
				if (!ft_strcmp(line, "exit"))
					break;
			}
		}
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
//	print_envl(&msh);
	msh_loop(&msh);
//	msh_clean(&msh, 1);
//	exit(msh.exit_code);
}
