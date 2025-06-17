/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_extract.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 20:10:53 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/17 07:05:47 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*errout_retnull(char *buf)
{
	if (buf)
		free(buf);
	printf_fd(STDERR_FILENO, "minishell: error retrieving current process id"
		"\n");
	return (NULL);
}

char	*get_process_pid(char *buf, int fd)
{
	char	*tmp;
	int		bytes_read;

	if (!buf)
		return (errout_retnull(buf));
	fd = open("/proc/self/stat", O_RDONLY);
	if (fd == -1)
		return (errout_retnull(buf));
	bytes_read = read(fd, buf, PID_MAX_LEN - 1);
	if (bytes_read == -1)
		return (errout_retnull(buf));
	if (fd != -1)
		close(fd);
	tmp = buf;
	while (bytes_read-- && !ft_strchr(" \t\n\r\f\v", *tmp))
		tmp++;
	*tmp = 0;
	return (buf);
}

char	*extract_exp_value(t_msh *msh, char *key)
{
	char	*env_var;

	if (!ft_strcmp(key, "?"))
		return (ft_itoa(msh -> exit_code));
	else if (!ft_strcmp(key, "$"))
		return (get_process_pid(malloc(PID_MAX_LEN), -1));
	else if (!ft_strcmp(key, "0"))
		return (ft_strdup("minishell"));
	else
	{
		env_var = get_env(msh -> envl, key);
		if (env_var)
			return (ft_strdup(env_var));
		else
			return (ft_strdup(""));
	}
}
