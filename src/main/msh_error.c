/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msh_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wweerasi <wweerasi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:31:28 by wweerasi          #+#    #+#             */
/*   Updated: 2025/06/18 11:12:46 by wweerasi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	error_log(char *err_msg, char *param, int err_no, int extrarg)
{
	t_errnote	*err_note;

	if (extrarg)
	{
		err_note = (t_errnote *) param;
		printf_fd(STDERR_FILENO, err_msg, err_note -> cmd_path, err_note
			->strerr);
	}
	else if (param && err_no)
		printf_fd(STDERR_FILENO, err_msg, param, strerror(err_no));
	else if (param && !err_no)
		printf_fd(STDERR_FILENO, err_msg, param);
	else if (!param && err_no)
		printf_fd(STDERR_FILENO, err_msg, strerror(err_no));
	else
		printf_fd(STDERR_FILENO, err_msg);
	if (!ft_strcmp(err_msg, ERR_DUP)) //used this free ft_itoa(fd) which was used to write te error message for dup fail. 
		free(param);
}

void	msh_error(t_msh *msh, t_do_err opt_exc, char *err_msg, char *param)
{
	int	opt;
	int	errsv;
	int	extrarg;

	opt = (opt_exc >> 8) & 0xFF;
	errsv = 0;
	extrarg = 0;
	msh -> exit_code = opt_exc & 0xFF;
	if (opt & ERRNO)
		errsv = errno;
	if (opt & EXTRARG)
		extrarg = 1;
	if (opt & LOG)
		error_log(err_msg, param, errsv, extrarg);
	if (opt & CLEAN)
		msh_clean(msh);
	if (opt & EXIT)
		exit(msh -> exit_code);
}
