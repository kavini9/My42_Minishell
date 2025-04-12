/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:57:09 by wweerasi          #+#    #+#             */
/*   Updated: 2025/04/12 22:30:58 by wweerasi         ###   ########.fr       */
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
			//pipex -> err_note = strerror(errno);
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
	else
		return ;
	if (!arr_path)
		printf("path arr split failed. free nothing in this function");//TODO: error handling. no mallocs done.
}

char	*get_cmd_path(t_msh *msh, t_cmd *cmd, char *cmd_name, char **arr_path)
{
	char	*cmd_path;
	char	*tmp;

	arr_path = get_path_array(msh, msh -> envl);
	while (arr_path && *arr_path)
	{
		cmd_path = ft_strjoin("/", cmd_name);
		tmp = cmd_path;
		if (cmd_path)
			cmd_path = ft_strjoin(*arr_path, tmp);
		if (tmp)
			free(tmp);
		if (!cmd_path)
			printf("cmd_path: malloc failed\n");//TODO: error handling
		if (access_check(msh, cmd, cmd_path) == 0)
			return (cmd_path);
		free(cmd_path);
		arr_path++;
	}
	if (cmd -> cmd_exit_code != X_KO)
		cmd -> cmd_exit_code = F_KO;
	// if (pipex -> err_note == NULL)
	// 	pipex -> err_note = CMD_NOT_FOUND;
	//free_arr(arr_path);//check if this needs to be null. this should be destroyed going out of this function.
	return (ft_strdup(cmd_name));
}

void    execute_cmd(t_msh *msh, t_cmd *cmd)
{
    char **cmd_arr;
	char **arr_path;
    char *cmd_path;

	if (!execif_builtin(msh, cmd))
	{
    	cmd_arr = cmd -> cmd;
    	if (*cmd_arr && !ft_strchr(*cmd_arr, '/'))
        	cmd_path = get_cmd_path(msh, cmd, *cmd_arr, arr_path);
    	else if (*cmd_arr)
    	{
        	access_check(msh, cmd, *cmd_arr);
        	cmd_path = ft_strdup(*cmd_arr);
    	}
    	if (!cmd_path)
        	exit(printf("no need to free anything yet"));//TODO: Error handling
    	execve(cmd_path, cmd_arr, msh -> envl);
		free_arr(arr_path);
		free(cmd_path);
	}
	//clean and exit with exit code set in msh received.
    printf("execve failed. free cmd path and path arr");// clean all memeory and set exitcode for child proocess.
}