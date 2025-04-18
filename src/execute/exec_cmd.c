/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:57:09 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/18 23:26:11 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../includes/minishell.h"

int	access_check(t_msh *msh, t_cmd *cmd, char *cmd_path)
{
	if (access(cmd_path, F_OK) == 0)
	{
		if (access(cmd_path, X_OK) == 0)
			return (0);
		else
		{
			cmd -> cmd_exit_code = X_KO;
			cmd -> err_note.strerr = strerror(errno);
		}
	}
	else if (cmd -> cmd_exit_code != X_KO)
		cmd -> cmd_exit_code = F_KO;
	return (-1);
}

char	*get_path_array(t_msh *msh, char **envl)
{
	char *env_path;
    char *arr_path;

    env_path = get_env(envl, "PATH");
	if (*env_path)
        arr_path = ft_split(env_path, ':');
	else //can this go wrong when env is NULL i.e. env -i
		arr_path = ft_split(".", ' ');// will create {"./", NULL} so I can search current folder if the env path is unset.
	if (!arr_path)
		msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "split");//"minishell: fatal error: memory allocation failed in %s\n"
}

void	get_cmd_path(t_msh *msh, t_cmd *cmd, char *cmd_name, char **cmd_path)
{
	char	**arr_path;
	char	*tmp;

	arr_path = get_path_array(msh, msh -> envl);
	while (arr_path && *arr_path)
	{
		*cmd_path = ft_strjoin("/", cmd_name);
		tmp = *cmd_path;
		if (*cmd_path)
			*cmd_path = ft_strjoin(*arr_path, tmp);
		if (tmp)
			free(tmp);
		if (!*cmd_path)
			msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "exec");//"minishell: fatal error: memory allocation failed in %s\n"
		if (access_check(msh, cmd, *cmd_path) == 0)
			return (free_arr(arr_path));
		free(*cmd_path);
		arr_path++;
	}
	if (cmd -> cmd_exit_code != X_KO)
		cmd -> cmd_exit_code = F_KO;
	if (cmd -> err_note.strerr == NULL)
	 	cmd -> err_note.strerr = CMD_NOT_FOUND;
	free_arr(arr_path);//check if this needs to be null. this should be destroyed going out of this function.
	*cmd_path = ft_strdup(cmd_name);//this is protected in calling function
}

void    execute_cmd(t_msh *msh, t_cmd *cmd)
{
    char **cmd_arr;
    char *cmd_path;

	cmd_path = NULL;
	if (!execif_builtin(msh, cmd))
	{
    	cmd_arr = cmd -> cmd;
    	if (*cmd_arr && !ft_strchr(*cmd_arr, '/'))
        	get_cmd_path(msh, cmd, *cmd_arr, &cmd_path);
    	else if (*cmd_arr)
    	{
        	access_check(msh, cmd, *cmd_arr);
        	cmd_path = ft_strdup(*cmd_arr);
    	}
    	if (!cmd_path)
        	msh_error(msh, (LOG|CLEAN|EXIT) << 8 | 1, ERR_MALLOC, "execution");//"minishell: fatal error: memory allocation failed in %s\n"
    	execve(cmd_path, cmd_arr, msh -> envl);
		if (cmd -> err_note.strerr)
			cmd -> err_note.cmd_path = cmd_path;
		msh_error(msh, (ERRNO|LOG|CLEAN|EXIT) << 8 | 1, ERR_EXECVE,  (char *)&(cmd -> err_note));
		free(cmd_path);//see if this needs to be nulled
	}
	//clean and exit with exit code set in msh received.
	msh_error(msh, (ERRNO|LOG|CLEAN|EXIT) << 8 | 1, ERR_EXECVE, (char *)&(cmd -> err_note));
    //printf("execve failed. free cmd path and path arr\n");// clean all memeory and set exitcode for child proocess.
}