/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoshinth <aoshinth@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 14:41:10 by aoshinth          #+#    #+#             */
/*   Updated: 2025/04/09 14:56:13 by aoshinth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * init_heredoc - Initializes a file for heredoc input and sets up signals.
 *
 * @cmd: Pointer to the command structure.
 * @fd: Pointer to an integer to store the opened file descriptor.
 *
 * Returns: 0 on success, 1 on failure.
 */
static int	init_heredoc(t_cmd *cmd, int *fd)
{
	if (!cmd || !cmd->redir_end)
		return (1);
	*fd = open(cmd->redir_end->heredoc_name, O_RDWR | O_CREAT | O_EXCL, 0600);
	if (*fd == -1)
	{
		ft_putendl_fd("Failed to open temp file for heredoc", STDERR_FILENO);
		return (1);
	}
	signal(SIGINT, sig_handler_hd);
	return (0);
}

/**
 * restore_and_cleanup - Closes file descriptors and restores the saved stdin.
 *
 * @msh: Pointer to the shell (t_msh) structure.
 * @fd: File descriptor to close (if valid).
 * @exit_code: Exit code to return.
 *
 * Returns: The provided exit code after performing cleanup.
 */
int	restore_and_cleanup(t_msh *msh, int fd, int exit_code)
{
	if (fd != -1)
		close(fd);
	if (msh->stdin_saved != -1)
	{
		if (dup2(msh->stdin_saved, STDIN_FILENO) == -1)
			perror("Failed to restore original STDIN");
		close(msh->stdin_saved);
		msh->stdin_saved = -1;
	}
	return (exit_code);
}
/**
 * write_close_hd - Writes a line to a file descriptor and handles cleanup.
 *
 * @line: Line to write (NULL if only closing).
 * @fd: File descriptor.
 * @end: If true, close the file; otherwise write and free the line.
 */
static void	write_close_hd(char *line, int fd, int end)
{
	if (end)
	{
		close(fd);
		return;
	}
	if (line)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

/**
 * process_heredoc_line - Processes each line input during heredoc.
 *
 * @msh: Pointer to the shell (t_msh) structure.
 * @cmd: Pointer to the current command structure.
 * @line: The input line to process.
 * @fd: File descriptor of the heredoc file.
 *
 * Returns: 1 if delimiter is matched, -1 on error, 0 to continue.
 */
static int	process_heredoc_line(t_msh *msh, t_cmd *cmd, char *line, int fd)
{
	if (!line || ft_strcmp(line, cmd->redir_end->delimiter) == 0)
	{
		free(line);
		return (1);
	}
	if (check_expand(msh, cmd, &line, fd))
	{
		free(line);
		return (-1);
	}
	write_close_hd(line, fd, 0);
	return (0);
}





/**
 * open_and_write_to_heredoc - Handles heredoc logic,
 *                              including file creation and input processing.
 *
 * @msh: Pointer to the shell (t_msh) structure.
 * @cmd: Pointer to the current command structure (t_cmd).
 *
 * Creates a temporary file for the heredoc and processes input lines until the
 * delimiter is matched or an interruption occurs. Writes valid input lines to
 * the file. Returns 0 on success or 1 on failure.
 */
int	open_and_write_to_heredoc(t_msh *msh, t_cmd *cmd)
{
	int		fd;
	char	*line;
	int		result;

	msh->stdin_saved = dup(STDIN_FILENO);
	if (msh->stdin_saved == -1)
	{
		perror("Failed to save STDIN");
		return (1);
	}
	if (init_heredoc(cmd, &fd))
		return (restore_and_cleanup(msh, fd, 1));
	while (1)
	{
		line = readline("heredoc> ");
		if (g_signal == SIGINT)
		{
			free(line);
			return (restore_and_cleanup(msh, fd, 1));
		}
		result = process_heredoc_line(msh, cmd, line, fd);
		if (result == 1)
			break ;
		if (result == -1)
			return (restore_and_cleanup(msh, fd, 1));
	}
	write_close_hd(NULL, fd, 1);
	return (restore_and_cleanup(msh, -1, 0));
}





