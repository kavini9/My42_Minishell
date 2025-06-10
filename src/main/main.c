/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 18:32:56 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/09 22:13:55 by wweerasi         ###   ########.fr       */
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
	//msh -> exit_code = 0;this didnt change anything
}

void    msh_execute(t_msh *msh)
{
	here_doc(msh, msh -> cmd, msh -> hdocfd_l, 0);//what kind of errors can occur with this? pipe open, read and write to pipe
    if (msh -> cmd_count == 1 && is_builtin((*msh->cmd) -> cmd))//TODO: see the dereference here. see if it needs too be chnged in struct.
        execin_shell(msh, *msh -> cmd);
    else
	{
        execin_child(msh, msh -> cmd, -1, 0);
	}
	reset_cmd_attr(msh);
}

void	msh_parse(t_msh *msh, char *line)
{
	t_parse	aux;//in static memory remember to assign to cmd struct before leaving this function.

	msh -> aux = &aux;
	init_parse_structs(msh, line);
	line_split_bypipe(msh, line, msh -> aux -> seg);
    //print_segments(msh -> aux -> seg);//debugging purpose
	seg_tokenize(msh, msh -> aux);
    //print_tokens(msh -> aux -> token);//debugging purpose
    expand_tokens(msh, msh -> aux -> token);
	//print_expand_arrays(msh -> aux -> token);//debugging purpose
	init_cmd_struct(msh, msh -> cmd_count);
	setup_cmd(msh, msh -> aux -> token, msh -> cmd);
	//print_cmd_members(msh -> cmd);//debugging purpose
	clean_aux(msh, msh -> aux);
}

void	msh_loop(t_msh *msh)
{
	char	*line;
	
	while(1)
	{
		printf("in the loop 11111111111111111111111111111\n");
		if (isatty(fileno(stdin)))
            init_sig();
		printf("in the loop 2222222222222222222222222222222\n");
		line = readline("minishell> ");//looks like it reads from somewhere else sometimes? I didn't press enter?
		printf("in the loop 33333333333333333333333333333333\n");
		add_history(line);
		printf("in the loop 4444444444444444444444444444444\n");
		if (*line)
		{	
			printf("in the loop 55555555555555555555555555\n");
			if (!msh_validate_line(msh, &line)) 
			{
				printf("in the loop 666666666666666666666666666666666666\n");
				msh_parse(msh, line);
				msh -> exit_code = 0;//this is just a quick fix. 
				printf("in the loop 7777777777777777777777777777777777777777\n");
				msh_execute(msh);
				printf("in the loop 888888888888888888888888888888888888\n");
			}
			printf("exit_code: %i\n", msh -> exit_code);
		}
		free(line);//probably I am freeing this somewhere inside msh_parse as well. Double check it.
	}
	printf("in the loop 99999999999999999999999999999999\n");
	rl_clear_history();
	printf("in the loop 0000000000000000000000000000000000\n");
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
 